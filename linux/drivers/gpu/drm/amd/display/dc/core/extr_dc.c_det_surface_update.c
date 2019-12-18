#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int addr_update; int new_plane; int full_update; int in_transfer_func_change; int input_csc_change; int coeff_reduction_change; int gamma_change; } ;
union surface_update_flags {TYPE_2__ bits; scalar_t__ raw; } ;
struct dc_surface_update {TYPE_3__* surface; TYPE_1__* plane_info; scalar_t__ gamma; scalar_t__ coeff_reduction_factor; scalar_t__ input_csc_color_matrix; scalar_t__ in_transfer_func; scalar_t__ flip_addr; } ;
struct dc_state {int dummy; } ;
struct dc {struct dc_state* current_state; } ;
typedef  enum surface_update_type { ____Placeholder_surface_update_type } surface_update_type ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;
struct TYPE_6__ {int format; scalar_t__ force_full_update; union surface_update_flags update_flags; } ;
struct TYPE_4__ {int format; } ;

/* Variables and functions */
 int SURFACE_PIXEL_FORMAT_GRPH_BEGIN ; 
 int UPDATE_TYPE_FAST ; 
 int UPDATE_TYPE_FULL ; 
 int UPDATE_TYPE_MED ; 
 scalar_t__ dce_use_lut (int) ; 
 int /*<<< orphan*/  elevate_update_type (int*,int) ; 
 int get_plane_info_update_type (struct dc_surface_update const*) ; 
 int get_scaling_info_update_type (struct dc_surface_update const*) ; 
 int /*<<< orphan*/  is_surface_in_context (struct dc_state const*,TYPE_3__*) ; 

__attribute__((used)) static enum surface_update_type det_surface_update(const struct dc *dc,
		const struct dc_surface_update *u)
{
	const struct dc_state *context = dc->current_state;
	enum surface_update_type type;
	enum surface_update_type overall_type = UPDATE_TYPE_FAST;
	union surface_update_flags *update_flags = &u->surface->update_flags;

	update_flags->raw = 0; // Reset all flags

	if (u->flip_addr)
		update_flags->bits.addr_update = 1;

	if (!is_surface_in_context(context, u->surface)) {
		update_flags->bits.new_plane = 1;
		return UPDATE_TYPE_FULL;
	}

	if (u->surface->force_full_update) {
		update_flags->bits.full_update = 1;
		return UPDATE_TYPE_FULL;
	}

	type = get_plane_info_update_type(u);
	elevate_update_type(&overall_type, type);

	type = get_scaling_info_update_type(u);
	elevate_update_type(&overall_type, type);

	if (u->flip_addr)
		update_flags->bits.addr_update = 1;

	if (u->in_transfer_func)
		update_flags->bits.in_transfer_func_change = 1;

	if (u->input_csc_color_matrix)
		update_flags->bits.input_csc_change = 1;

	if (u->coeff_reduction_factor)
		update_flags->bits.coeff_reduction_change = 1;

	if (u->gamma) {
		enum surface_pixel_format format = SURFACE_PIXEL_FORMAT_GRPH_BEGIN;

		if (u->plane_info)
			format = u->plane_info->format;
		else if (u->surface)
			format = u->surface->format;

		if (dce_use_lut(format))
			update_flags->bits.gamma_change = 1;
	}

	if (update_flags->bits.in_transfer_func_change) {
		type = UPDATE_TYPE_MED;
		elevate_update_type(&overall_type, type);
	}

	if (update_flags->bits.input_csc_change
			|| update_flags->bits.coeff_reduction_change
			|| update_flags->bits.gamma_change) {
		type = UPDATE_TYPE_FULL;
		elevate_update_type(&overall_type, type);
	}

	return overall_type;
}