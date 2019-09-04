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
struct fmdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_RDS_HANDLE_RDS_GETCMD_RESP_IDX ; 
 int FM_RX_RDS_FIFO_THRESHOLD ; 
 int /*<<< orphan*/  RDS_DATA_GET ; 
 int /*<<< orphan*/  REG_RD ; 
 int /*<<< orphan*/  fm_irq_timeout_stage (struct fmdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fm_irq_send_rdsdata_getcmd(struct fmdev *fmdev)
{
	/* Send the command to read RDS data from the chip */
	if (!fm_send_cmd(fmdev, RDS_DATA_GET, REG_RD, NULL,
			    (FM_RX_RDS_FIFO_THRESHOLD * 3), NULL))
		fm_irq_timeout_stage(fmdev, FM_RDS_HANDLE_RDS_GETCMD_RESP_IDX);
}