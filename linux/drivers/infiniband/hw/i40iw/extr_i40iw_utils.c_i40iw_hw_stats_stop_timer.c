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
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

void i40iw_hw_stats_stop_timer(struct i40iw_sc_vsi *vsi)
{
	struct i40iw_vsi_pestat *devstat = vsi->pestat;

	del_timer_sync(&devstat->stats_timer);
}