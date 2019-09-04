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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ rds_mode; } ;
struct fmdev {scalar_t__ curr_fmmode; TYPE_1__ rx; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ FM_MODE_RX ; 
 scalar_t__ FM_RDS_SYSTEM_RBDS ; 
 scalar_t__ FM_RDS_SYSTEM_RDS ; 
 int /*<<< orphan*/  RDS_SYSTEM_SET ; 
 int /*<<< orphan*/  REG_WR ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmerr (char*) ; 

int fm_rx_set_rds_system(struct fmdev *fmdev, u8 rds_mode)
{
	u16 payload;
	int ret;

	if (fmdev->curr_fmmode != FM_MODE_RX)
		return -EPERM;

	if (rds_mode != FM_RDS_SYSTEM_RDS && rds_mode != FM_RDS_SYSTEM_RBDS) {
		fmerr("Invalid rds mode\n");
		return -EINVAL;
	}
	/* Set RDS operation mode */
	payload = (u16)rds_mode;
	ret = fmc_send_cmd(fmdev, RDS_SYSTEM_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	fmdev->rx.rds_mode = rds_mode;

	return 0;
}