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
struct falcon_nic_data {scalar_t__ stats_disable_count; struct ef4_nic* efx; } ;
struct ef4_nic {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  falcon_stats_complete (struct ef4_nic*) ; 
 int /*<<< orphan*/  falcon_stats_request (struct ef4_nic*) ; 
 struct falcon_nic_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct falcon_nic_data* nic_data ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_timer ; 

__attribute__((used)) static void falcon_stats_timer_func(struct timer_list *t)
{
	struct falcon_nic_data *nic_data = from_timer(nic_data, t,
						      stats_timer);
	struct ef4_nic *efx = nic_data->efx;

	spin_lock(&efx->stats_lock);

	falcon_stats_complete(efx);
	if (nic_data->stats_disable_count == 0)
		falcon_stats_request(efx);

	spin_unlock(&efx->stats_lock);
}