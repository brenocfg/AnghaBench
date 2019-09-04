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
typedef  int u32 ;
struct reg_whitelist {int size; int gen_mask; int /*<<< orphan*/  offset_ldw; int /*<<< orphan*/  offset_udw; } ;
struct drm_i915_reg_read {int offset; int /*<<< orphan*/  val; } ;
struct drm_i915_private {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int gen_mask; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct reg_whitelist*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ64_2x32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ8 (int /*<<< orphan*/ ) ; 
 unsigned int I915_REG_READ_8B_WA ; 
 TYPE_1__* INTEL_INFO (struct drm_i915_private*) ; 
 int i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 struct reg_whitelist* reg_read_whitelist ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

int i915_reg_read_ioctl(struct drm_device *dev,
			void *data, struct drm_file *file)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_i915_reg_read *reg = data;
	struct reg_whitelist const *entry;
	unsigned int flags;
	int remain;
	int ret = 0;

	entry = reg_read_whitelist;
	remain = ARRAY_SIZE(reg_read_whitelist);
	while (remain) {
		u32 entry_offset = i915_mmio_reg_offset(entry->offset_ldw);

		GEM_BUG_ON(!is_power_of_2(entry->size));
		GEM_BUG_ON(entry->size > 8);
		GEM_BUG_ON(entry_offset & (entry->size - 1));

		if (INTEL_INFO(dev_priv)->gen_mask & entry->gen_mask &&
		    entry_offset == (reg->offset & -entry->size))
			break;
		entry++;
		remain--;
	}

	if (!remain)
		return -EINVAL;

	flags = reg->offset & (entry->size - 1);

	intel_runtime_pm_get(dev_priv);
	if (entry->size == 8 && flags == I915_REG_READ_8B_WA)
		reg->val = I915_READ64_2x32(entry->offset_ldw,
					    entry->offset_udw);
	else if (entry->size == 8 && flags == 0)
		reg->val = I915_READ64(entry->offset_ldw);
	else if (entry->size == 4 && flags == 0)
		reg->val = I915_READ(entry->offset_ldw);
	else if (entry->size == 2 && flags == 0)
		reg->val = I915_READ16(entry->offset_ldw);
	else if (entry->size == 1 && flags == 0)
		reg->val = I915_READ8(entry->offset_ldw);
	else
		ret = -EINVAL;
	intel_runtime_pm_put(dev_priv);

	return ret;
}