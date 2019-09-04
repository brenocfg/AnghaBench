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
struct drm_i915_gem_object {int /*<<< orphan*/  frontbuffer_bits; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int I915_MAX_PIPES ; 
 int INTEL_FRONTBUFFER_BITS_PER_PIPE ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 int /*<<< orphan*/  atomic_andnot (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_or (unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 

void i915_gem_track_fb(struct drm_i915_gem_object *old,
		       struct drm_i915_gem_object *new,
		       unsigned frontbuffer_bits)
{
	/* Control of individual bits within the mask are guarded by
	 * the owning plane->mutex, i.e. we can never see concurrent
	 * manipulation of individual bits. But since the bitfield as a whole
	 * is updated using RMW, we need to use atomics in order to update
	 * the bits.
	 */
	BUILD_BUG_ON(INTEL_FRONTBUFFER_BITS_PER_PIPE * I915_MAX_PIPES >
		     sizeof(atomic_t) * BITS_PER_BYTE);

	if (old) {
		WARN_ON(!(atomic_read(&old->frontbuffer_bits) & frontbuffer_bits));
		atomic_andnot(frontbuffer_bits, &old->frontbuffer_bits);
	}

	if (new) {
		WARN_ON(atomic_read(&new->frontbuffer_bits) & frontbuffer_bits);
		atomic_or(frontbuffer_bits, &new->frontbuffer_bits);
	}
}