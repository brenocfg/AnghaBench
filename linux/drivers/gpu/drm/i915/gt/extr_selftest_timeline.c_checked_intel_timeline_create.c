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
struct intel_timeline {scalar_t__* hwsp_seqno; scalar_t__ seqno; } ;
struct drm_i915_private {int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct intel_timeline* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct intel_timeline*) ; 
 struct intel_timeline* intel_timeline_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_timeline_put (struct intel_timeline*) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct intel_timeline *
checked_intel_timeline_create(struct drm_i915_private *i915)
{
	struct intel_timeline *tl;

	tl = intel_timeline_create(&i915->gt, NULL);
	if (IS_ERR(tl))
		return tl;

	if (*tl->hwsp_seqno != tl->seqno) {
		pr_err("Timeline created with incorrect breadcrumb, found %x, expected %x\n",
		       *tl->hwsp_seqno, tl->seqno);
		intel_timeline_put(tl);
		return ERR_PTR(-EINVAL);
	}

	return tl;
}