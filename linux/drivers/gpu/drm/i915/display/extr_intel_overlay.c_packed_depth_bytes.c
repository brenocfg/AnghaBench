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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int I915_OVERLAY_DEPTH_MASK ; 
#define  I915_OVERLAY_YUV411 129 
#define  I915_OVERLAY_YUV422 128 

__attribute__((used)) static int packed_depth_bytes(u32 format)
{
	switch (format & I915_OVERLAY_DEPTH_MASK) {
	case I915_OVERLAY_YUV422:
		return 4;
	case I915_OVERLAY_YUV411:
		/* return 6; not implemented */
	default:
		return -EINVAL;
	}
}