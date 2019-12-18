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
struct intel_guc_ct_channel {int /*<<< orphan*/  vma; int /*<<< orphan*/  owner; } ;
struct intel_guc_ct {struct intel_guc_ct_channel host_channel; } ;
struct intel_guc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 struct intel_guc* ct_to_guc (struct intel_guc_ct*) ; 
 int ctch_init (struct intel_guc*,struct intel_guc_ct_channel*) ; 
 scalar_t__ unlikely (int) ; 

int intel_guc_ct_init(struct intel_guc_ct *ct)
{
	struct intel_guc *guc = ct_to_guc(ct);
	struct intel_guc_ct_channel *ctch = &ct->host_channel;
	int err;

	err = ctch_init(guc, ctch);
	if (unlikely(err)) {
		DRM_ERROR("CT: can't open channel %d; err=%d\n",
			  ctch->owner, err);
		return err;
	}

	GEM_BUG_ON(!ctch->vma);
	return 0;
}