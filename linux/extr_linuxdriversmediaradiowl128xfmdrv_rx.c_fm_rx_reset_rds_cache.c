#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mask; } ;
struct TYPE_6__ {scalar_t__ rd_idx; scalar_t__ wr_idx; scalar_t__ last_blk_idx; int /*<<< orphan*/  flag; } ;
struct TYPE_5__ {scalar_t__ af_mode; TYPE_3__ rds; } ;
struct fmdev {TYPE_1__ irq_info; TYPE_2__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_LEV_EVENT ; 
 int /*<<< orphan*/  FM_RDS_DISABLE ; 
 scalar_t__ FM_RX_RDS_AF_SWITCH_MODE_ON ; 

void fm_rx_reset_rds_cache(struct fmdev *fmdev)
{
	fmdev->rx.rds.flag = FM_RDS_DISABLE;
	fmdev->rx.rds.last_blk_idx = 0;
	fmdev->rx.rds.wr_idx = 0;
	fmdev->rx.rds.rd_idx = 0;

	if (fmdev->rx.af_mode == FM_RX_RDS_AF_SWITCH_MODE_ON)
		fmdev->irq_info.mask |= FM_LEV_EVENT;
}