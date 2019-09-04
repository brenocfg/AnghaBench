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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ovfl_trash; int /*<<< orphan*/  vci_trash; int /*<<< orphan*/  hec_err; int /*<<< orphan*/  atm_ovfl; } ;
struct lanai_dev {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ STATS_GET_BAD_VCI (int /*<<< orphan*/ ) ; 
 scalar_t__ STATS_GET_BUF_OVFL (int /*<<< orphan*/ ) ; 
 scalar_t__ STATS_GET_FIFO_OVFL (int /*<<< orphan*/ ) ; 
 scalar_t__ STATS_GET_HEC_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Statistics_Reg ; 
 int /*<<< orphan*/  reg_read (struct lanai_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_statistics(struct lanai_dev *lanai)
{
	u32 statreg = reg_read(lanai, Statistics_Reg);
	lanai->stats.atm_ovfl += STATS_GET_FIFO_OVFL(statreg);
	lanai->stats.hec_err += STATS_GET_HEC_ERR(statreg);
	lanai->stats.vci_trash += STATS_GET_BAD_VCI(statreg);
	lanai->stats.ovfl_trash += STATS_GET_BUF_OVFL(statreg);
}