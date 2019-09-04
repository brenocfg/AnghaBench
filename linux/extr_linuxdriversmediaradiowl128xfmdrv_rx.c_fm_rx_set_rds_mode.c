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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {scalar_t__ flag; scalar_t__ rd_idx; scalar_t__ wr_idx; scalar_t__ last_blk_idx; } ;
struct TYPE_6__ {TYPE_2__ rds; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask; } ;
struct fmdev {TYPE_3__ rx; TYPE_1__ irq_info; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FLAG_GET ; 
 scalar_t__ FM_RDS_DISABLE ; 
 scalar_t__ FM_RDS_ENABLE ; 
 int /*<<< orphan*/  FM_RDS_EVENT ; 
 int /*<<< orphan*/  FM_RX_PWR_SET_FM_AND_RDS_BLK_ON ; 
 int /*<<< orphan*/  FM_RX_PWR_SET_FM_ON_RDS_OFF ; 
 int /*<<< orphan*/  FM_RX_RDS_FIFO_THRESHOLD ; 
 int /*<<< orphan*/  FM_RX_RDS_FLUSH_FIFO ; 
 int /*<<< orphan*/  INT_MASK_SET ; 
 int /*<<< orphan*/  POWER_SET ; 
 int /*<<< orphan*/  RDS_CNTRL_SET ; 
 int /*<<< orphan*/  RDS_MEM_SET ; 
 int /*<<< orphan*/  REG_RD ; 
 int /*<<< orphan*/  REG_WR ; 
 int /*<<< orphan*/  fm_rx_reset_station_info (struct fmdev*) ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmerr (char*) ; 

int fm_rx_set_rds_mode(struct fmdev *fmdev, u8 rds_en_dis)
{
	u16 payload;
	int ret;

	if (rds_en_dis != FM_RDS_ENABLE && rds_en_dis != FM_RDS_DISABLE) {
		fmerr("Invalid rds option\n");
		return -EINVAL;
	}

	if (rds_en_dis == FM_RDS_ENABLE
	    && fmdev->rx.rds.flag == FM_RDS_DISABLE) {
		/* Turn on RX RDS and RDS circuit */
		payload = FM_RX_PWR_SET_FM_AND_RDS_BLK_ON;
		ret = fmc_send_cmd(fmdev, POWER_SET, REG_WR, &payload,
				sizeof(payload), NULL, NULL);
		if (ret < 0)
			return ret;

		/* Clear and reset RDS FIFO */
		payload = FM_RX_RDS_FLUSH_FIFO;
		ret = fmc_send_cmd(fmdev, RDS_CNTRL_SET, REG_WR, &payload,
		sizeof(payload), NULL, NULL);
		if (ret < 0)
			return ret;

		/* Read flags - just to clear any pending interrupts. */
		ret = fmc_send_cmd(fmdev, FLAG_GET, REG_RD, NULL, 2,
				NULL, NULL);
		if (ret < 0)
			return ret;

		/* Set RDS FIFO threshold value */
		payload = FM_RX_RDS_FIFO_THRESHOLD;
		ret = fmc_send_cmd(fmdev, RDS_MEM_SET, REG_WR, &payload,
		sizeof(payload), NULL, NULL);
		if (ret < 0)
			return ret;

		/* Enable RDS interrupt */
		fmdev->irq_info.mask |= FM_RDS_EVENT;
		payload = fmdev->irq_info.mask;
		ret = fmc_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
				sizeof(payload), NULL, NULL);
		if (ret < 0) {
			fmdev->irq_info.mask &= ~FM_RDS_EVENT;
			return ret;
		}

		/* Update our local flag */
		fmdev->rx.rds.flag = FM_RDS_ENABLE;
	} else if (rds_en_dis == FM_RDS_DISABLE
		   && fmdev->rx.rds.flag == FM_RDS_ENABLE) {
		/* Turn off RX RDS */
		payload = FM_RX_PWR_SET_FM_ON_RDS_OFF;
		ret = fmc_send_cmd(fmdev, POWER_SET, REG_WR, &payload,
				sizeof(payload), NULL, NULL);
		if (ret < 0)
			return ret;

		/* Reset RDS pointers */
		fmdev->rx.rds.last_blk_idx = 0;
		fmdev->rx.rds.wr_idx = 0;
		fmdev->rx.rds.rd_idx = 0;
		fm_rx_reset_station_info(fmdev);

		/* Update RDS local cache */
		fmdev->irq_info.mask &= ~(FM_RDS_EVENT);
		fmdev->rx.rds.flag = FM_RDS_DISABLE;
	}

	return 0;
}