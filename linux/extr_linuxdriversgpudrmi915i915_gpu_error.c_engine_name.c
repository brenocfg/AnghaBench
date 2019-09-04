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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 char const* __engine_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  engine_lookup (struct drm_i915_private const*,unsigned int) ; 

__attribute__((used)) static const char *
engine_name(const struct drm_i915_private *i915, unsigned int id)
{
	return __engine_name(engine_lookup(i915, id));
}