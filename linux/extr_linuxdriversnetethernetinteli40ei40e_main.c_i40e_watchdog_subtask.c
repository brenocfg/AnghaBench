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
struct i40e_pf {int flags; int num_alloc_vsi; scalar_t__* veb; TYPE_1__** vsi; int /*<<< orphan*/  state; scalar_t__ service_timer_previous; scalar_t__ service_timer_period; } ;
struct TYPE_2__ {scalar_t__ netdev; } ;

/* Variables and functions */
 int I40E_FLAG_LINK_POLLING_ENABLED ; 
 int I40E_FLAG_VEB_STATS_ENABLED ; 
 int I40E_MAX_VEB ; 
 int /*<<< orphan*/  __I40E_CONFIG_BUSY ; 
 int /*<<< orphan*/  __I40E_DOWN ; 
 int /*<<< orphan*/  __I40E_TEMP_LINK_POLLING ; 
 int /*<<< orphan*/  i40e_link_event (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_ptp_rx_hang (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_ptp_tx_hang (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_update_stats (TYPE_1__*) ; 
 int /*<<< orphan*/  i40e_update_veb_stats (scalar_t__) ; 
 scalar_t__ jiffies ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void i40e_watchdog_subtask(struct i40e_pf *pf)
{
	int i;

	/* if interface is down do nothing */
	if (test_bit(__I40E_DOWN, pf->state) ||
	    test_bit(__I40E_CONFIG_BUSY, pf->state))
		return;

	/* make sure we don't do these things too often */
	if (time_before(jiffies, (pf->service_timer_previous +
				  pf->service_timer_period)))
		return;
	pf->service_timer_previous = jiffies;

	if ((pf->flags & I40E_FLAG_LINK_POLLING_ENABLED) ||
	    test_bit(__I40E_TEMP_LINK_POLLING, pf->state))
		i40e_link_event(pf);

	/* Update the stats for active netdevs so the network stack
	 * can look at updated numbers whenever it cares to
	 */
	for (i = 0; i < pf->num_alloc_vsi; i++)
		if (pf->vsi[i] && pf->vsi[i]->netdev)
			i40e_update_stats(pf->vsi[i]);

	if (pf->flags & I40E_FLAG_VEB_STATS_ENABLED) {
		/* Update the stats for the active switching components */
		for (i = 0; i < I40E_MAX_VEB; i++)
			if (pf->veb[i])
				i40e_update_veb_stats(pf->veb[i]);
	}

	i40e_ptp_rx_hang(pf);
	i40e_ptp_tx_hang(pf);
}