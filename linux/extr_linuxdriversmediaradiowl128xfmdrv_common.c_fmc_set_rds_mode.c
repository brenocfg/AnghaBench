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
typedef  int /*<<< orphan*/  u8 ;
struct fmdev {int curr_fmmode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FM_MODE_RX 129 
#define  FM_MODE_TX 128 
 int fm_rx_set_rds_mode (struct fmdev*,int /*<<< orphan*/ ) ; 
 int fm_tx_set_rds_mode (struct fmdev*,int /*<<< orphan*/ ) ; 

int fmc_set_rds_mode(struct fmdev *fmdev, u8 rds_en_dis)
{
	switch (fmdev->curr_fmmode) {
	case FM_MODE_RX:
		return fm_rx_set_rds_mode(fmdev, rds_en_dis);

	case FM_MODE_TX:
		return fm_tx_set_rds_mode(fmdev, rds_en_dis);

	default:
		return -EINVAL;
	}
}