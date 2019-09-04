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
struct inode {struct drm_i915_private* i_private; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  log; } ;
struct drm_i915_private {TYPE_1__ guc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  USES_GUC (struct drm_i915_private*) ; 
 int intel_guc_log_relay_open (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i915_guc_log_relay_open(struct inode *inode, struct file *file)
{
	struct drm_i915_private *dev_priv = inode->i_private;

	if (!USES_GUC(dev_priv))
		return -ENODEV;

	file->private_data = &dev_priv->guc.log;

	return intel_guc_log_relay_open(&dev_priv->guc.log);
}