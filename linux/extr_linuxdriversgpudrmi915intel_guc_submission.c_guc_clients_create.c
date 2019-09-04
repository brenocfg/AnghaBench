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
struct intel_guc_client {int dummy; } ;
struct intel_guc {struct intel_guc_client* preempt_client; struct intel_guc_client* execbuf_client; } ;
struct drm_i915_private {scalar_t__ preempt_context; scalar_t__ kernel_context; } ;
struct TYPE_2__ {int /*<<< orphan*/  ring_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GEM_BUG_ON (struct intel_guc_client*) ; 
 int /*<<< orphan*/  GUC_CLIENT_PRIORITY_KMD_HIGH ; 
 int /*<<< orphan*/  GUC_CLIENT_PRIORITY_KMD_NORMAL ; 
 TYPE_1__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct intel_guc_client*) ; 
 int PTR_ERR (struct intel_guc_client*) ; 
 struct intel_guc_client* guc_client_alloc (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  guc_client_free (struct intel_guc_client*) ; 
 int /*<<< orphan*/  guc_fill_preempt_context (struct intel_guc*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 

__attribute__((used)) static int guc_clients_create(struct intel_guc *guc)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);
	struct intel_guc_client *client;

	GEM_BUG_ON(guc->execbuf_client);
	GEM_BUG_ON(guc->preempt_client);

	client = guc_client_alloc(dev_priv,
				  INTEL_INFO(dev_priv)->ring_mask,
				  GUC_CLIENT_PRIORITY_KMD_NORMAL,
				  dev_priv->kernel_context);
	if (IS_ERR(client)) {
		DRM_ERROR("Failed to create GuC client for submission!\n");
		return PTR_ERR(client);
	}
	guc->execbuf_client = client;

	if (dev_priv->preempt_context) {
		client = guc_client_alloc(dev_priv,
					  INTEL_INFO(dev_priv)->ring_mask,
					  GUC_CLIENT_PRIORITY_KMD_HIGH,
					  dev_priv->preempt_context);
		if (IS_ERR(client)) {
			DRM_ERROR("Failed to create GuC client for preemption!\n");
			guc_client_free(guc->execbuf_client);
			guc->execbuf_client = NULL;
			return PTR_ERR(client);
		}
		guc->preempt_client = client;

		guc_fill_preempt_context(guc);
	}

	return 0;
}