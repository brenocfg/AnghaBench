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
struct intel_guc_ct_channel {int dummy; } ;
struct intel_guc_ct {struct intel_guc_ct_channel host_channel; } ;
struct intel_guc {int /*<<< orphan*/  handler; int /*<<< orphan*/  send; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  HAS_GUC_CT (struct drm_i915_private*) ; 
 struct intel_guc* ct_to_guc (struct intel_guc_ct*) ; 
 int ctch_open (struct intel_guc*,struct intel_guc_ct_channel*) ; 
 int /*<<< orphan*/  enableddisabled (int) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_send_ct ; 
 int /*<<< orphan*/  intel_guc_to_host_event_handler_ct ; 
 scalar_t__ unlikely (int) ; 

int intel_guc_ct_enable(struct intel_guc_ct *ct)
{
	struct intel_guc *guc = ct_to_guc(ct);
	struct drm_i915_private *i915 = guc_to_i915(guc);
	struct intel_guc_ct_channel *ctch = &ct->host_channel;
	int err;

	GEM_BUG_ON(!HAS_GUC_CT(i915));

	err = ctch_open(guc, ctch);
	if (unlikely(err))
		return err;

	/* Switch into cmd transport buffer based send() */
	guc->send = intel_guc_send_ct;
	guc->handler = intel_guc_to_host_event_handler_ct;
	DRM_INFO("CT: %s\n", enableddisabled(true));
	return 0;
}