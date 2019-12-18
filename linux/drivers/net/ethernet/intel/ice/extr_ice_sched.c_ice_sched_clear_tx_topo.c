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
struct ice_port_info {int /*<<< orphan*/ * root; } ;

/* Variables and functions */
 int /*<<< orphan*/  ice_free_sched_node (struct ice_port_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ice_sched_clear_tx_topo(struct ice_port_info *pi)
{
	if (!pi)
		return;
	if (pi->root) {
		ice_free_sched_node(pi, pi->root);
		pi->root = NULL;
	}
}