#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int len; int /*<<< orphan*/  offset; int /*<<< orphan*/  page; } ;
struct hfa384x {scalar_t__ dlstate; TYPE_2__* wlandev; TYPE_1__ bufinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int HFA384x_ADDR_AUX_MKFLAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HFA384x_ADDR_CMD_MKOFF (int) ; 
 int /*<<< orphan*/  HFA384x_ADDR_CMD_MKPAGE (int) ; 
 scalar_t__ HFA384x_DLSTATE_FLASHENABLED ; 
 int /*<<< orphan*/  HFA384x_PROGMODE_NV ; 
 int /*<<< orphan*/  HFA384x_PROGMODE_NVWRITE ; 
 int HFA384x_USB_RWMEM_MAXLEN ; 
 int hfa384x_cmd_download (struct hfa384x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hfa384x_dowmem (struct hfa384x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 

int hfa384x_drvr_flashdl_write(struct hfa384x *hw, u32 daddr,
			       void *buf, u32 len)
{
	int result = 0;
	u32 dlbufaddr;
	int nburns;
	u32 burnlen;
	u32 burndaddr;
	u16 burnlo;
	u16 burnhi;
	int nwrites;
	u8 *writebuf;
	u16 writepage;
	u16 writeoffset;
	u32 writelen;
	int i;
	int j;

	pr_debug("daddr=0x%08x len=%d\n", daddr, len);

	/* Check that we're in the flash download state */
	if (hw->dlstate != HFA384x_DLSTATE_FLASHENABLED)
		return -EINVAL;

	netdev_info(hw->wlandev->netdev,
		    "Download %d bytes to flash @0x%06x\n", len, daddr);

	/* Convert to flat address for arithmetic */
	/* NOTE: dlbuffer RID stores the address in AUX format */
	dlbufaddr =
	    HFA384x_ADDR_AUX_MKFLAT(hw->bufinfo.page, hw->bufinfo.offset);
	pr_debug("dlbuf.page=0x%04x dlbuf.offset=0x%04x dlbufaddr=0x%08x\n",
		 hw->bufinfo.page, hw->bufinfo.offset, dlbufaddr);
	/* Calculations to determine how many fills of the dlbuffer to do
	 * and how many USB wmemreq's to do for each fill.  At this point
	 * in time, the dlbuffer size and the wmemreq size are the same.
	 * Therefore, nwrites should always be 1.  The extra complexity
	 * here is a hedge against future changes.
	 */

	/* Figure out how many times to do the flash programming */
	nburns = len / hw->bufinfo.len;
	nburns += (len % hw->bufinfo.len) ? 1 : 0;

	/* For each flash program cycle, how many USB wmemreq's are needed? */
	nwrites = hw->bufinfo.len / HFA384x_USB_RWMEM_MAXLEN;
	nwrites += (hw->bufinfo.len % HFA384x_USB_RWMEM_MAXLEN) ? 1 : 0;

	/* For each burn */
	for (i = 0; i < nburns; i++) {
		/* Get the dest address and len */
		burnlen = (len - (hw->bufinfo.len * i)) > hw->bufinfo.len ?
		    hw->bufinfo.len : (len - (hw->bufinfo.len * i));
		burndaddr = daddr + (hw->bufinfo.len * i);
		burnlo = HFA384x_ADDR_CMD_MKOFF(burndaddr);
		burnhi = HFA384x_ADDR_CMD_MKPAGE(burndaddr);

		netdev_info(hw->wlandev->netdev, "Writing %d bytes to flash @0x%06x\n",
			    burnlen, burndaddr);

		/* Set the download mode */
		result = hfa384x_cmd_download(hw, HFA384x_PROGMODE_NV,
					      burnlo, burnhi, burnlen);
		if (result) {
			netdev_err(hw->wlandev->netdev,
				   "download(NV,lo=%x,hi=%x,len=%x) cmd failed, result=%d. Aborting d/l\n",
				   burnlo, burnhi, burnlen, result);
			goto exit_proc;
		}

		/* copy the data to the flash download buffer */
		for (j = 0; j < nwrites; j++) {
			writebuf = buf +
			    (i * hw->bufinfo.len) +
			    (j * HFA384x_USB_RWMEM_MAXLEN);

			writepage = HFA384x_ADDR_CMD_MKPAGE(dlbufaddr +
						(j * HFA384x_USB_RWMEM_MAXLEN));
			writeoffset = HFA384x_ADDR_CMD_MKOFF(dlbufaddr +
						(j * HFA384x_USB_RWMEM_MAXLEN));

			writelen = burnlen - (j * HFA384x_USB_RWMEM_MAXLEN);
			writelen = writelen > HFA384x_USB_RWMEM_MAXLEN ?
			    HFA384x_USB_RWMEM_MAXLEN : writelen;

			result = hfa384x_dowmem(hw,
						writepage,
						writeoffset,
						writebuf, writelen);
		}

		/* set the download 'write flash' mode */
		result = hfa384x_cmd_download(hw,
					      HFA384x_PROGMODE_NVWRITE,
					      0, 0, 0);
		if (result) {
			netdev_err(hw->wlandev->netdev,
				   "download(NVWRITE,lo=%x,hi=%x,len=%x) cmd failed, result=%d. Aborting d/l\n",
				   burnlo, burnhi, burnlen, result);
			goto exit_proc;
		}

		/* TODO: We really should do a readback and compare. */
	}

exit_proc:

	/* Leave the firmware in the 'post-prog' mode.  flashdl_disable will */
	/*  actually disable programming mode.  Remember, that will cause the */
	/*  the firmware to effectively reset itself. */

	return result;
}