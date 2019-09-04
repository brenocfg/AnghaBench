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
struct intel_guc_client {scalar_t__ engines; int priority; scalar_t__ doorbell_id; struct i915_gem_context* owner; int /*<<< orphan*/  guc; } ;
struct i915_gem_context {int dummy; } ;
struct drm_i915_private {struct i915_gem_context* kernel_context; struct i915_gem_context* preempt_context; } ;
struct TYPE_2__ {scalar_t__ ring_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GUC_DOORBELL_INVALID ; 
 TYPE_1__* INTEL_INFO (struct drm_i915_private*) ; 
 struct drm_i915_private* guc_to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_client(struct intel_guc_client *client,
			   int client_priority,
			   bool is_preempt_client)
{
	struct drm_i915_private *dev_priv = guc_to_i915(client->guc);
	struct i915_gem_context *ctx_owner = is_preempt_client ?
			dev_priv->preempt_context : dev_priv->kernel_context;

	if (client->owner != ctx_owner ||
	    client->engines != INTEL_INFO(dev_priv)->ring_mask ||
	    client->priority != client_priority ||
	    client->doorbell_id == GUC_DOORBELL_INVALID)
		return -EINVAL;
	else
		return 0;
}