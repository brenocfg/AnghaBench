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
struct intel_guc_client {int /*<<< orphan*/  stage_id; TYPE_2__* guc; TYPE_1__* vma; } ;
struct TYPE_4__ {int /*<<< orphan*/  stage_ids; } ;
struct TYPE_3__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  guc_stage_desc_fini (TYPE_2__*,struct intel_guc_client*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_unpin_and_release (TYPE_1__**) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct intel_guc_client*) ; 
 int /*<<< orphan*/  unreserve_doorbell (struct intel_guc_client*) ; 

__attribute__((used)) static void guc_client_free(struct intel_guc_client *client)
{
	unreserve_doorbell(client);
	guc_stage_desc_fini(client->guc, client);
	i915_gem_object_unpin_map(client->vma->obj);
	i915_vma_unpin_and_release(&client->vma);
	ida_simple_remove(&client->guc->stage_ids, client->stage_id);
	kfree(client);
}