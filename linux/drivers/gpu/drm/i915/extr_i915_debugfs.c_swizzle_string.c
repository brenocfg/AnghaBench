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

/* Variables and functions */
#define  I915_BIT_6_SWIZZLE_9 135 
#define  I915_BIT_6_SWIZZLE_9_10 134 
#define  I915_BIT_6_SWIZZLE_9_10_11 133 
#define  I915_BIT_6_SWIZZLE_9_10_17 132 
#define  I915_BIT_6_SWIZZLE_9_11 131 
#define  I915_BIT_6_SWIZZLE_9_17 130 
#define  I915_BIT_6_SWIZZLE_NONE 129 
#define  I915_BIT_6_SWIZZLE_UNKNOWN 128 

__attribute__((used)) static const char *swizzle_string(unsigned swizzle)
{
	switch (swizzle) {
	case I915_BIT_6_SWIZZLE_NONE:
		return "none";
	case I915_BIT_6_SWIZZLE_9:
		return "bit9";
	case I915_BIT_6_SWIZZLE_9_10:
		return "bit9/bit10";
	case I915_BIT_6_SWIZZLE_9_11:
		return "bit9/bit11";
	case I915_BIT_6_SWIZZLE_9_10_11:
		return "bit9/bit10/bit11";
	case I915_BIT_6_SWIZZLE_9_17:
		return "bit9/bit17";
	case I915_BIT_6_SWIZZLE_9_10_17:
		return "bit9/bit10/bit17";
	case I915_BIT_6_SWIZZLE_UNKNOWN:
		return "unknown";
	}

	return "bug";
}