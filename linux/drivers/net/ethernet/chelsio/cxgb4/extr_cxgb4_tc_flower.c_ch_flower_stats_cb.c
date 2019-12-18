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
struct timer_list {int dummy; } ;
struct adapter {int /*<<< orphan*/  flower_stats_work; } ;

/* Variables and functions */
 struct adapter* adap ; 
 int /*<<< orphan*/  flower_stats_timer ; 
 struct adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ch_flower_stats_cb(struct timer_list *t)
{
	struct adapter *adap = from_timer(adap, t, flower_stats_timer);

	schedule_work(&adap->flower_stats_work);
}