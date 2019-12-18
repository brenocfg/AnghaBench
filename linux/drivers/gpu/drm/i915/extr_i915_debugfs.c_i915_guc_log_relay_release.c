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
struct intel_guc {int /*<<< orphan*/  log; } ;
struct inode {struct drm_i915_private* i_private; } ;
struct file {int dummy; } ;
struct TYPE_3__ {struct intel_guc guc; } ;
struct TYPE_4__ {TYPE_1__ uc; } ;
struct drm_i915_private {TYPE_2__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_guc_log_relay_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i915_guc_log_relay_release(struct inode *inode, struct file *file)
{
	struct drm_i915_private *i915 = inode->i_private;
	struct intel_guc *guc = &i915->gt.uc.guc;

	intel_guc_log_relay_close(&guc->log);
	return 0;
}