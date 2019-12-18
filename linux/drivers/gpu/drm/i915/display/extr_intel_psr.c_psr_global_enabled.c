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
struct TYPE_2__ {int enable_psr; } ;

/* Variables and functions */
#define  I915_PSR_DEBUG_DEFAULT 129 
#define  I915_PSR_DEBUG_DISABLE 128 
 int I915_PSR_DEBUG_MODE_MASK ; 
 TYPE_1__ i915_modparams ; 

__attribute__((used)) static bool psr_global_enabled(u32 debug)
{
	switch (debug & I915_PSR_DEBUG_MODE_MASK) {
	case I915_PSR_DEBUG_DEFAULT:
		return i915_modparams.enable_psr;
	case I915_PSR_DEBUG_DISABLE:
		return false;
	default:
		return true;
	}
}