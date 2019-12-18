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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct intel_plane {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int
g4x_sprite_max_stride(struct intel_plane *plane,
		      u32 pixel_format, u64 modifier,
		      unsigned int rotation)
{
	return 16384;
}