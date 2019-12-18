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
struct TYPE_2__ {scalar_t__ function; } ;
struct adapter {int tc_flower_initialized; int /*<<< orphan*/  flower_tbl; int /*<<< orphan*/  flower_stats_work; TYPE_1__ flower_stats_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

void cxgb4_cleanup_tc_flower(struct adapter *adap)
{
	if (!adap->tc_flower_initialized)
		return;

	if (adap->flower_stats_timer.function)
		del_timer_sync(&adap->flower_stats_timer);
	cancel_work_sync(&adap->flower_stats_work);
	rhashtable_destroy(&adap->flower_tbl);
	adap->tc_flower_initialized = false;
}