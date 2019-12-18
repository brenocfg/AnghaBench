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
struct i40iw_vsi_pestat {int /*<<< orphan*/  stats_timer; } ;
struct i40iw_sc_vsi {struct i40iw_vsi_pestat* pestat; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_TIMER_DELAY ; 
 int /*<<< orphan*/  i40iw_hw_stats_timeout ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i40iw_hw_stats_start_timer(struct i40iw_sc_vsi *vsi)
{
	struct i40iw_vsi_pestat *devstat = vsi->pestat;

	timer_setup(&devstat->stats_timer, i40iw_hw_stats_timeout, 0);
	mod_timer(&devstat->stats_timer,
		  jiffies + msecs_to_jiffies(STATS_TIMER_DELAY));
}