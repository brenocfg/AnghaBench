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
typedef  int /*<<< orphan*/  u8 ;
typedef  int const u32 ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {scalar_t__ is_mobile; } ;

/* Variables and functions */
 TYPE_1__* INTEL_INFO (struct drm_i915_private*) ; 
 int _pxvid_to_vd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 pvid_to_extvid(struct drm_i915_private *dev_priv, u8 pxvid)
{
	const int vd = _pxvid_to_vd(pxvid);
	const int vm = vd - 1125;

	if (INTEL_INFO(dev_priv)->is_mobile)
		return vm > 0 ? vm : 0;

	return vd;
}