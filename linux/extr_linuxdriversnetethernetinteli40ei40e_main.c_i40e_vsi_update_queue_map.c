#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * tc_mapping; int /*<<< orphan*/  queue_mapping; int /*<<< orphan*/  mapping_flags; } ;
struct i40e_vsi_context {TYPE_2__ info; } ;
struct TYPE_3__ {int /*<<< orphan*/  tc_mapping; int /*<<< orphan*/  queue_mapping; int /*<<< orphan*/  mapping_flags; } ;
struct i40e_vsi {TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void i40e_vsi_update_queue_map(struct i40e_vsi *vsi,
				      struct i40e_vsi_context *ctxt)
{
	/* copy just the sections touched not the entire info
	 * since not all sections are valid as returned by
	 * update vsi params
	 */
	vsi->info.mapping_flags = ctxt->info.mapping_flags;
	memcpy(&vsi->info.queue_mapping,
	       &ctxt->info.queue_mapping, sizeof(vsi->info.queue_mapping));
	memcpy(&vsi->info.tc_mapping, ctxt->info.tc_mapping,
	       sizeof(vsi->info.tc_mapping));
}