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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u16 ;
struct vgt_if {int dummy; } ;
struct TYPE_2__ {int active; int /*<<< orphan*/  caps; } ;
struct drm_i915_private {TYPE_1__ vgpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 scalar_t__ VGT_MAGIC ; 
 int VGT_PVINFO_SIZE ; 
 scalar_t__ VGT_VERSION_MAJOR ; 
 scalar_t__ __raw_i915_read16 (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_i915_read32 (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ __raw_i915_read64 (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ vgt_caps ; 
 int /*<<< orphan*/  vgtif_reg (scalar_t__) ; 

void i915_check_vgpu(struct drm_i915_private *dev_priv)
{
	u64 magic;
	u16 version_major;

	BUILD_BUG_ON(sizeof(struct vgt_if) != VGT_PVINFO_SIZE);

	magic = __raw_i915_read64(dev_priv, vgtif_reg(magic));
	if (magic != VGT_MAGIC)
		return;

	version_major = __raw_i915_read16(dev_priv, vgtif_reg(version_major));
	if (version_major < VGT_VERSION_MAJOR) {
		DRM_INFO("VGT interface version mismatch!\n");
		return;
	}

	dev_priv->vgpu.caps = __raw_i915_read32(dev_priv, vgtif_reg(vgt_caps));

	dev_priv->vgpu.active = true;
	DRM_INFO("Virtual GPU for Intel GVT-g detected.\n");
}