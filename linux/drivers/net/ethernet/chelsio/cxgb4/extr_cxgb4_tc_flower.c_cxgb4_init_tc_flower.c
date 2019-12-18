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
struct adapter {int tc_flower_initialized; int /*<<< orphan*/  flower_stats_timer; int /*<<< orphan*/  flower_stats_work; int /*<<< orphan*/  flower_ht_params; int /*<<< orphan*/  flower_tbl; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ STATS_CHECK_PERIOD ; 
 int /*<<< orphan*/  ch_flower_stats_cb ; 
 int /*<<< orphan*/  ch_flower_stats_handler ; 
 int /*<<< orphan*/  cxgb4_tc_flower_ht_params ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cxgb4_init_tc_flower(struct adapter *adap)
{
	int ret;

	if (adap->tc_flower_initialized)
		return -EEXIST;

	adap->flower_ht_params = cxgb4_tc_flower_ht_params;
	ret = rhashtable_init(&adap->flower_tbl, &adap->flower_ht_params);
	if (ret)
		return ret;

	INIT_WORK(&adap->flower_stats_work, ch_flower_stats_handler);
	timer_setup(&adap->flower_stats_timer, ch_flower_stats_cb, 0);
	mod_timer(&adap->flower_stats_timer, jiffies + STATS_CHECK_PERIOD);
	adap->tc_flower_initialized = true;
	return 0;
}