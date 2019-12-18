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
typedef  int u16 ;
struct fmdev {scalar_t__ curr_fmmode; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ FM_MODE_TX ; 
 int /*<<< orphan*/  RDS_DATA_ENB ; 
 int /*<<< orphan*/  REG_WR ; 
 int /*<<< orphan*/  fm_tx_set_rds_mode (struct fmdev*,int /*<<< orphan*/ ) ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_rds_data_mode (struct fmdev*,int) ; 
 int /*<<< orphan*/  set_rds_len (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_rds_text (struct fmdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

int fm_tx_set_radio_text(struct fmdev *fmdev, u8 *rds_text, u8 rds_type)
{
	u16 payload;
	int ret;

	if (fmdev->curr_fmmode != FM_MODE_TX)
		return -EPERM;

	fm_tx_set_rds_mode(fmdev, 0);

	/* Set RDS length */
	set_rds_len(fmdev, rds_type, strlen(rds_text));

	/* Set RDS text */
	set_rds_text(fmdev, rds_text);

	/* Set RDS mode */
	set_rds_data_mode(fmdev, 0x0);

	payload = 1;
	ret = fmc_send_cmd(fmdev, RDS_DATA_ENB, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	return 0;
}