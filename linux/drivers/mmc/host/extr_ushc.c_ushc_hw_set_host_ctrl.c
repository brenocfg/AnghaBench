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
typedef  int u16 ;
struct ushc_data {int host_ctrl; int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USHC_HOST_CTRL ; 
 int /*<<< orphan*/  USHC_HOST_CTRL_TYPE ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ushc_hw_set_host_ctrl(struct ushc_data *ushc, u16 mask, u16 val)
{
	u16 host_ctrl;
	int ret;

	host_ctrl = (ushc->host_ctrl & ~mask) | val;
	ret = usb_control_msg(ushc->usb_dev, usb_sndctrlpipe(ushc->usb_dev, 0),
			      USHC_HOST_CTRL, USHC_HOST_CTRL_TYPE,
			      host_ctrl, 0, NULL, 0, 100);
	if (ret < 0)
		return ret;
	ushc->host_ctrl = host_ctrl;
	return 0;
}