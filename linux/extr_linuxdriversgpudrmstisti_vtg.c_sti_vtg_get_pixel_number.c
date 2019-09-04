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
typedef  scalar_t__ u32 ;
struct drm_display_mode {scalar_t__ hsync_start; scalar_t__ htotal; } ;

/* Variables and functions */

u32 sti_vtg_get_pixel_number(struct drm_display_mode mode, int x)
{
	return mode.htotal - mode.hsync_start + x;
}