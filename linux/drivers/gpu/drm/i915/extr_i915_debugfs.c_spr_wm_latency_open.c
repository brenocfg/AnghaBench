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
struct inode {struct drm_i915_private* i_private; } ;
struct file {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 int single_open (struct file*,int /*<<< orphan*/ ,struct drm_i915_private*) ; 
 int /*<<< orphan*/  spr_wm_latency_show ; 

__attribute__((used)) static int spr_wm_latency_open(struct inode *inode, struct file *file)
{
	struct drm_i915_private *dev_priv = inode->i_private;

	if (HAS_GMCH(dev_priv))
		return -ENODEV;

	return single_open(file, spr_wm_latency_show, dev_priv);
}