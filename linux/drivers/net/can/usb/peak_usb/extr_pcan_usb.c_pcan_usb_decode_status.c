#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct pcan_usb_msg_context {int* ptr; int* end; int /*<<< orphan*/  netdev; int /*<<< orphan*/  rec_ts_idx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCAN_USB_CMD_ARGS ; 
 size_t PCAN_USB_CMD_FUNC ; 
 size_t PCAN_USB_CMD_NUM ; 
 int PCAN_USB_ERROR_TXQFULL ; 
#define  PCAN_USB_REC_ANALOG 132 
#define  PCAN_USB_REC_BUSEVT 131 
#define  PCAN_USB_REC_BUSLOAD 130 
#define  PCAN_USB_REC_ERROR 129 
#define  PCAN_USB_REC_TS 128 
 int PCAN_USB_STATUSLEN_DLC ; 
 int PCAN_USB_STATUSLEN_TIMESTAMP ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int pcan_usb_decode_error (struct pcan_usb_msg_context*,int,int) ; 
 int pcan_usb_decode_ts (struct pcan_usb_msg_context*,int) ; 
 int /*<<< orphan*/  pcan_usb_update_ts (struct pcan_usb_msg_context*) ; 

__attribute__((used)) static int pcan_usb_decode_status(struct pcan_usb_msg_context *mc,
				  u8 status_len)
{
	u8 rec_len = status_len & PCAN_USB_STATUSLEN_DLC;
	u8 f, n;
	int err;

	/* check whether function and number can be read */
	if ((mc->ptr + 2) > mc->end)
		return -EINVAL;

	f = mc->ptr[PCAN_USB_CMD_FUNC];
	n = mc->ptr[PCAN_USB_CMD_NUM];
	mc->ptr += PCAN_USB_CMD_ARGS;

	if (status_len & PCAN_USB_STATUSLEN_TIMESTAMP) {
		int err = pcan_usb_decode_ts(mc, !mc->rec_ts_idx);

		if (err)
			return err;

		/* Next packet in the buffer will have a timestamp on a single
		 * byte
		 */
		mc->rec_ts_idx++;
	}

	switch (f) {
	case PCAN_USB_REC_ERROR:
		err = pcan_usb_decode_error(mc, n, status_len);
		if (err)
			return err;
		break;

	case PCAN_USB_REC_ANALOG:
		/* analog values (ignored) */
		rec_len = 2;
		break;

	case PCAN_USB_REC_BUSLOAD:
		/* bus load (ignored) */
		rec_len = 1;
		break;

	case PCAN_USB_REC_TS:
		/* only timestamp */
		if (pcan_usb_update_ts(mc))
			return -EINVAL;
		break;

	case PCAN_USB_REC_BUSEVT:
		/* error frame/bus event */
		if (n & PCAN_USB_ERROR_TXQFULL)
			netdev_dbg(mc->netdev, "device Tx queue full)\n");
		break;
	default:
		netdev_err(mc->netdev, "unexpected function %u\n", f);
		break;
	}

	if ((mc->ptr + rec_len) > mc->end)
		return -EINVAL;

	mc->ptr += rec_len;

	return 0;
}