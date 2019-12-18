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
struct TYPE_2__ {int /*<<< orphan*/  last_hibern8_exit_tstamp; scalar_t__ hibern8_exit_cnt; } ;
struct ufs_hba {scalar_t__ req_abort_count; TYPE_1__ ufs_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ufshcd_clear_dbg_ufs_stats(struct ufs_hba *hba)
{
	hba->ufs_stats.hibern8_exit_cnt = 0;
	hba->ufs_stats.last_hibern8_exit_tstamp = ktime_set(0, 0);
	hba->req_abort_count = 0;
}