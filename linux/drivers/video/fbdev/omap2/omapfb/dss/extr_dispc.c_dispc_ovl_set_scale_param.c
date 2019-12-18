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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum omap_color_component { ____Placeholder_omap_color_component } omap_color_component ;

/* Variables and functions */
 int /*<<< orphan*/  dispc_ovl_set_fir (int,int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_scale_coef (int,int,int,int,int) ; 

__attribute__((used)) static void dispc_ovl_set_scale_param(enum omap_plane plane,
		u16 orig_width, u16 orig_height,
		u16 out_width, u16 out_height,
		bool five_taps, u8 rotation,
		enum omap_color_component color_comp)
{
	int fir_hinc, fir_vinc;

	fir_hinc = 1024 * orig_width / out_width;
	fir_vinc = 1024 * orig_height / out_height;

	dispc_ovl_set_scale_coef(plane, fir_hinc, fir_vinc, five_taps,
				color_comp);
	dispc_ovl_set_fir(plane, fir_hinc, fir_vinc, color_comp);
}