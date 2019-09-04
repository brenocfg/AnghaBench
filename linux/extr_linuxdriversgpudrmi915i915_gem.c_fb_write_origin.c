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
struct drm_i915_gem_object {int frontbuffer_ggtt_origin; } ;
typedef  enum fb_op_origin { ____Placeholder_fb_op_origin } fb_op_origin ;

/* Variables and functions */
 unsigned int I915_GEM_DOMAIN_GTT ; 
 int ORIGIN_CPU ; 

__attribute__((used)) static inline enum fb_op_origin
fb_write_origin(struct drm_i915_gem_object *obj, unsigned int domain)
{
	return (domain == I915_GEM_DOMAIN_GTT ?
		obj->frontbuffer_ggtt_origin : ORIGIN_CPU);
}