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
struct iwl_mvm {int aux_queue; int probe_queue; int p2p_dev_queue; int snif_queue; } ;

/* Variables and functions */

__attribute__((used)) static int iwl_mvm_is_static_queue(struct iwl_mvm *mvm, int queue)
{
	return queue == mvm->aux_queue || queue == mvm->probe_queue ||
		queue == mvm->p2p_dev_queue || queue == mvm->snif_queue;
}