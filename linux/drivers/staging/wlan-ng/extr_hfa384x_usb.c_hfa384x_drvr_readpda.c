#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct pdaloc   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct hfa384x {TYPE_1__* wlandev; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct pdaloc {int /*<<< orphan*/  cardaddr; int auxctl; } ;
struct TYPE_3__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 int ENODATA ; 
 int /*<<< orphan*/  HFA3841_PDA_BASE ; 
 int /*<<< orphan*/  HFA3841_PDA_BOGUS_BASE ; 
 int /*<<< orphan*/  HFA3842_PDA_BASE ; 
 int HFA384x_ADDR_CMD_MKOFF (int /*<<< orphan*/ ) ; 
 int HFA384x_ADDR_CMD_MKPAGE (int /*<<< orphan*/ ) ; 
 int HFA384x_PDR_END_OF_PDA ; 
 int HFA384x_PDR_LEN_MAX ; 
 int hfa384x_dormem (struct hfa384x*,int,int,void*,unsigned int) ; 
 int /*<<< orphan*/  hfa384x_isgood_pdrcode (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

int hfa384x_drvr_readpda(struct hfa384x *hw, void *buf, unsigned int len)
{
	int result = 0;
	__le16 *pda = buf;
	int pdaok = 0;
	int morepdrs = 1;
	int currpdr = 0;	/* word offset of the current pdr */
	size_t i;
	u16 pdrlen;		/* pdr length in bytes, host order */
	u16 pdrcode;		/* pdr code, host order */
	u16 currpage;
	u16 curroffset;
	struct pdaloc {
		u32 cardaddr;
		u16 auxctl;
	} pdaloc[] = {
		{
		HFA3842_PDA_BASE, 0}, {
		HFA3841_PDA_BASE, 0}, {
		HFA3841_PDA_BOGUS_BASE, 0}
	};

	/* Read the pda from each known address.  */
	for (i = 0; i < ARRAY_SIZE(pdaloc); i++) {
		/* Make address */
		currpage = HFA384x_ADDR_CMD_MKPAGE(pdaloc[i].cardaddr);
		curroffset = HFA384x_ADDR_CMD_MKOFF(pdaloc[i].cardaddr);

		/* units of bytes */
		result = hfa384x_dormem(hw, currpage, curroffset, buf,
					len);

		if (result) {
			netdev_warn(hw->wlandev->netdev,
				    "Read from index %zd failed, continuing\n",
				    i);
			continue;
		}

		/* Test for garbage */
		pdaok = 1;	/* initially assume good */
		morepdrs = 1;
		while (pdaok && morepdrs) {
			pdrlen = le16_to_cpu(pda[currpdr]) * 2;
			pdrcode = le16_to_cpu(pda[currpdr + 1]);
			/* Test the record length */
			if (pdrlen > HFA384x_PDR_LEN_MAX || pdrlen == 0) {
				netdev_err(hw->wlandev->netdev,
					   "pdrlen invalid=%d\n", pdrlen);
				pdaok = 0;
				break;
			}
			/* Test the code */
			if (!hfa384x_isgood_pdrcode(pdrcode)) {
				netdev_err(hw->wlandev->netdev, "pdrcode invalid=%d\n",
					   pdrcode);
				pdaok = 0;
				break;
			}
			/* Test for completion */
			if (pdrcode == HFA384x_PDR_END_OF_PDA)
				morepdrs = 0;

			/* Move to the next pdr (if necessary) */
			if (morepdrs) {
				/* note the access to pda[], need words here */
				currpdr += le16_to_cpu(pda[currpdr]) + 1;
			}
		}
		if (pdaok) {
			netdev_info(hw->wlandev->netdev,
				    "PDA Read from 0x%08x in %s space.\n",
				    pdaloc[i].cardaddr,
				    pdaloc[i].auxctl == 0 ? "EXTDS" :
				    pdaloc[i].auxctl == 1 ? "NV" :
				    pdaloc[i].auxctl == 2 ? "PHY" :
				    pdaloc[i].auxctl == 3 ? "ICSRAM" :
				    "<bogus auxctl>");
			break;
		}
	}
	result = pdaok ? 0 : -ENODATA;

	if (result)
		pr_debug("Failure: pda is not okay\n");

	return result;
}