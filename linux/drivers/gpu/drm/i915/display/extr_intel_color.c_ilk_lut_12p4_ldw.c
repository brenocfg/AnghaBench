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
struct drm_color_lut {int red; int green; int blue; } ;

/* Variables and functions */

__attribute__((used)) static u32 ilk_lut_12p4_ldw(const struct drm_color_lut *color)
{
	return (color->red & 0x3f) << 24 | (color->green & 0x3f) << 14 |
		(color->blue & 0x3f) << 4;
}