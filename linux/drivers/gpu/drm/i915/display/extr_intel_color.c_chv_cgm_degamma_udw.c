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
typedef  int /*<<< orphan*/  u32 ;
struct drm_color_lut {int /*<<< orphan*/  red; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_color_lut_extract (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 chv_cgm_degamma_udw(const struct drm_color_lut *color)
{
	return drm_color_lut_extract(color->red, 14);
}