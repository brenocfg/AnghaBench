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
typedef  int uint32_t ;
struct TYPE_2__ {int embedded_panel_h_size; int embedded_panel_v_size; } ;
struct dce112_compressor {TYPE_1__ base; } ;

/* Variables and functions */

__attribute__((used)) static bool is_source_bigger_than_epanel_size(
	struct dce112_compressor *cp110,
	uint32_t source_view_width,
	uint32_t source_view_height)
{
	if (cp110->base.embedded_panel_h_size != 0 &&
		cp110->base.embedded_panel_v_size != 0 &&
		((source_view_width * source_view_height) >
		(cp110->base.embedded_panel_h_size *
			cp110->base.embedded_panel_v_size)))
		return true;

	return false;
}