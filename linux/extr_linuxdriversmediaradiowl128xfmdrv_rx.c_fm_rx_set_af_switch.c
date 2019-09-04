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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ af_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask; } ;
struct fmdev {scalar_t__ curr_fmmode; TYPE_1__ rx; TYPE_2__ irq_info; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  FM_LEV_EVENT ; 
 scalar_t__ FM_MODE_RX ; 
 scalar_t__ FM_RX_RDS_AF_SWITCH_MODE_OFF ; 
 scalar_t__ FM_RX_RDS_AF_SWITCH_MODE_ON ; 
 int /*<<< orphan*/  INT_MASK_SET ; 
 int /*<<< orphan*/  REG_WR ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmerr (char*) ; 

int fm_rx_set_af_switch(struct fmdev *fmdev, u8 af_mode)
{
	u16 payload;
	int ret;

	if (fmdev->curr_fmmode != FM_MODE_RX)
		return -EPERM;

	if (af_mode != FM_RX_RDS_AF_SWITCH_MODE_ON &&
	    af_mode != FM_RX_RDS_AF_SWITCH_MODE_OFF) {
		fmerr("Invalid af mode\n");
		return -EINVAL;
	}
	/* Enable/disable low RSSI interrupt based on af_mode */
	if (af_mode == FM_RX_RDS_AF_SWITCH_MODE_ON)
		fmdev->irq_info.mask |= FM_LEV_EVENT;
	else
		fmdev->irq_info.mask &= ~FM_LEV_EVENT;

	payload = fmdev->irq_info.mask;
	ret = fmc_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	fmdev->rx.af_mode = af_mode;

	return 0;
}