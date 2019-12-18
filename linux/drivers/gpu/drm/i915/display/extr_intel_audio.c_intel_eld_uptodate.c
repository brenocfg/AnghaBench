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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_connector {int /*<<< orphan*/ * eld; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  const I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_eld_size (int /*<<< orphan*/  const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_eld_uptodate(struct drm_connector *connector,
			       i915_reg_t reg_eldv, u32 bits_eldv,
			       i915_reg_t reg_elda, u32 bits_elda,
			       i915_reg_t reg_edid)
{
	struct drm_i915_private *dev_priv = to_i915(connector->dev);
	const u8 *eld = connector->eld;
	u32 tmp;
	int i;

	tmp = I915_READ(reg_eldv);
	tmp &= bits_eldv;

	if (!tmp)
		return false;

	tmp = I915_READ(reg_elda);
	tmp &= ~bits_elda;
	I915_WRITE(reg_elda, tmp);

	for (i = 0; i < drm_eld_size(eld) / 4; i++)
		if (I915_READ(reg_edid) != *((const u32 *)eld + i))
			return false;

	return true;
}