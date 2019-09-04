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
struct ice_pf {int num_alloc_vsi; TYPE_1__** vsi; scalar_t__ serv_tmr_prev; scalar_t__ serv_tmr_period; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {scalar_t__ netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ICE_CFG_BUSY ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  ice_update_pf_stats (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_update_vsi_stats (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ice_watchdog_subtask(struct ice_pf *pf)
{
	int i;

	/* if interface is down do nothing */
	if (test_bit(__ICE_DOWN, pf->state) ||
	    test_bit(__ICE_CFG_BUSY, pf->state))
		return;

	/* make sure we don't do these things too often */
	if (time_before(jiffies,
			pf->serv_tmr_prev + pf->serv_tmr_period))
		return;

	pf->serv_tmr_prev = jiffies;

	/* Update the stats for active netdevs so the network stack
	 * can look at updated numbers whenever it cares to
	 */
	ice_update_pf_stats(pf);
	for (i = 0; i < pf->num_alloc_vsi; i++)
		if (pf->vsi[i] && pf->vsi[i]->netdev)
			ice_update_vsi_stats(pf->vsi[i]);
}