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
struct i40e_pfc_stats {int /*<<< orphan*/  priority_xon_2_xoff; int /*<<< orphan*/  priority_xoff_tx; int /*<<< orphan*/  priority_xon_tx; int /*<<< orphan*/  priority_xoff_rx; int /*<<< orphan*/  priority_xon_rx; } ;
struct TYPE_2__ {int /*<<< orphan*/ * priority_xon_2_xoff; int /*<<< orphan*/ * priority_xoff_tx; int /*<<< orphan*/ * priority_xon_tx; int /*<<< orphan*/ * priority_xoff_rx; int /*<<< orphan*/ * priority_xon_rx; } ;
struct i40e_pf {TYPE_1__ stats; } ;

/* Variables and functions */

__attribute__((used)) static inline struct i40e_pfc_stats
i40e_get_pfc_stats(struct i40e_pf *pf, unsigned int i)
{
#define I40E_GET_PFC_STAT(stat, priority) \
	.stat = pf->stats.stat[priority]

	struct i40e_pfc_stats pfc = {
		I40E_GET_PFC_STAT(priority_xon_rx, i),
		I40E_GET_PFC_STAT(priority_xoff_rx, i),
		I40E_GET_PFC_STAT(priority_xon_tx, i),
		I40E_GET_PFC_STAT(priority_xoff_tx, i),
		I40E_GET_PFC_STAT(priority_xon_2_xoff, i),
	};
	return pfc;
}