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
typedef  size_t u8 ;
struct intel_engine_cs {int dummy; } ;
struct drm_i915_private {struct intel_engine_cs*** engine_class; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t*) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 size_t MAX_ENGINE_CLASS ; 
 size_t MAX_ENGINE_INSTANCE ; 
 size_t* user_class_map ; 

struct intel_engine_cs *
intel_engine_lookup_user(struct drm_i915_private *i915, u8 class, u8 instance)
{
	if (class >= ARRAY_SIZE(user_class_map))
		return NULL;

	class = user_class_map[class];

	GEM_BUG_ON(class > MAX_ENGINE_CLASS);

	if (instance > MAX_ENGINE_INSTANCE)
		return NULL;

	return i915->engine_class[class][instance];
}