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
struct intel_guc_client {int /*<<< orphan*/  stage_id; TYPE_1__* guc; int /*<<< orphan*/  vma; } ;
struct TYPE_2__ {int /*<<< orphan*/  stage_ids; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_VMA_RELEASE_MAP ; 
 int /*<<< orphan*/  i915_vma_unpin_and_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct intel_guc_client*) ; 
 int /*<<< orphan*/  unreserve_doorbell (struct intel_guc_client*) ; 

__attribute__((used)) static void guc_client_free(struct intel_guc_client *client)
{
	unreserve_doorbell(client);
	i915_vma_unpin_and_release(&client->vma, I915_VMA_RELEASE_MAP);
	ida_simple_remove(&client->guc->stage_ids, client->stage_id);
	kfree(client);
}