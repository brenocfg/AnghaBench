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
struct TYPE_6__ {int /*<<< orphan*/  enable; int /*<<< orphan*/  settime64; int /*<<< orphan*/  gettime64; int /*<<< orphan*/  adjtime; int /*<<< orphan*/  adjfreq; scalar_t__ pps; scalar_t__ n_per_out; scalar_t__ n_ext_ts; scalar_t__ n_alarm; int /*<<< orphan*/  max_adj; int /*<<< orphan*/  name; int /*<<< orphan*/  owner; } ;
struct bnx2x {int /*<<< orphan*/ * ptp_clock; TYPE_2__* pdev; TYPE_3__ ptp_clock_info; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MAX_PHC_DRIFT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bnx2x_ptp_adjfreq ; 
 int /*<<< orphan*/  bnx2x_ptp_adjtime ; 
 int /*<<< orphan*/  bnx2x_ptp_enable ; 
 int /*<<< orphan*/  bnx2x_ptp_gettime ; 
 int /*<<< orphan*/  bnx2x_ptp_settime ; 
 int /*<<< orphan*/ * ptp_clock_register (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

void bnx2x_register_phc(struct bnx2x *bp)
{
	/* Fill the ptp_clock_info struct and register PTP clock*/
	bp->ptp_clock_info.owner = THIS_MODULE;
	snprintf(bp->ptp_clock_info.name, 16, "%s", bp->dev->name);
	bp->ptp_clock_info.max_adj = BNX2X_MAX_PHC_DRIFT; /* In PPB */
	bp->ptp_clock_info.n_alarm = 0;
	bp->ptp_clock_info.n_ext_ts = 0;
	bp->ptp_clock_info.n_per_out = 0;
	bp->ptp_clock_info.pps = 0;
	bp->ptp_clock_info.adjfreq = bnx2x_ptp_adjfreq;
	bp->ptp_clock_info.adjtime = bnx2x_ptp_adjtime;
	bp->ptp_clock_info.gettime64 = bnx2x_ptp_gettime;
	bp->ptp_clock_info.settime64 = bnx2x_ptp_settime;
	bp->ptp_clock_info.enable = bnx2x_ptp_enable;

	bp->ptp_clock = ptp_clock_register(&bp->ptp_clock_info, &bp->pdev->dev);
	if (IS_ERR(bp->ptp_clock)) {
		bp->ptp_clock = NULL;
		BNX2X_ERR("PTP clock registration failed\n");
	}
}