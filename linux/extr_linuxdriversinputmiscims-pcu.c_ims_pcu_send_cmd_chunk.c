#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ims_pcu {int /*<<< orphan*/  dev; int /*<<< orphan*/  urb_out_buf; TYPE_1__* ep_out; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMS_PCU_CMD_WRITE_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ims_pcu_send_cmd_chunk(struct ims_pcu *pcu,
				  u8 command, int chunk, int len)
{
	int error;

	error = usb_bulk_msg(pcu->udev,
			     usb_sndbulkpipe(pcu->udev,
					     pcu->ep_out->bEndpointAddress),
			     pcu->urb_out_buf, len,
			     NULL, IMS_PCU_CMD_WRITE_TIMEOUT);
	if (error < 0) {
		dev_dbg(pcu->dev,
			"Sending 0x%02x command failed at chunk %d: %d\n",
			command, chunk, error);
		return error;
	}

	return 0;
}