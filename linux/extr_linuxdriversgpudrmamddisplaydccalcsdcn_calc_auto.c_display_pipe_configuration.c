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
struct dcn_bw_internal_vars {double* total_number_of_active_dpp_per_ratio; int number_of_active_planes; int** dpp_per_plane_per_ratio; scalar_t__* dispclk_dppclk_support_per_ratio; double* required_dispclk_per_ratio; int dispclk_dppclk_ratio; int* dpp_per_plane; scalar_t__* source_pixel_format; double byte_per_pix_dety; double byte_per_pix_detc; scalar_t__* source_surface_mode; double read256_bytes_block_height_y; double read256_bytes_block_width_y; double read256_bytes_block_height_c; double read256_bytes_block_width_c; scalar_t__* source_scan; double maximum_swath_height_y; double maximum_swath_height_c; double minimum_swath_height_y; double minimum_swath_height_c; scalar_t__ bug_forcing_luma_and_chroma_request_to_same_size_fixed; int swath_width; int* viewport_width; int* viewport_height; double swath_width_granularity_y; int rounded_up_max_swath_size_bytes_y; double swath_width_granularity_c; int rounded_up_max_swath_size_bytes_c; double det_buffer_size_in_kbyte; int* swath_height_y; int* swath_height_c; double* det_buffer_size_y; double* det_buffer_size_c; int /*<<< orphan*/ * error_message; int /*<<< orphan*/  final_error_message; } ;

/* Variables and functions */
 int dcn_bw_ceil2 (double,double) ; 
 scalar_t__ dcn_bw_hor ; 
 scalar_t__ dcn_bw_no ; 
 scalar_t__ dcn_bw_rgb_sub_16 ; 
 scalar_t__ dcn_bw_rgb_sub_32 ; 
 scalar_t__ dcn_bw_rgb_sub_64 ; 
 scalar_t__ dcn_bw_sw_4_kb_s ; 
 scalar_t__ dcn_bw_sw_4_kb_s_x ; 
 scalar_t__ dcn_bw_sw_64_kb_s ; 
 scalar_t__ dcn_bw_sw_64_kb_s_t ; 
 scalar_t__ dcn_bw_sw_64_kb_s_x ; 
 scalar_t__ dcn_bw_sw_linear ; 
 scalar_t__ dcn_bw_sw_var_s ; 
 scalar_t__ dcn_bw_sw_var_s_x ; 
 scalar_t__ dcn_bw_yes ; 
 scalar_t__ dcn_bw_yuv420_sub_10 ; 
 scalar_t__ dcn_bw_yuv420_sub_8 ; 

void display_pipe_configuration(struct dcn_bw_internal_vars *v)
{
	int j;
	int k;
	/*display pipe configuration*/

	for (j = 0; j <= 1; j++) {
		v->total_number_of_active_dpp_per_ratio[j] = 0.0;
		for (k = 0; k <= v->number_of_active_planes - 1; k++) {
			v->total_number_of_active_dpp_per_ratio[j] = v->total_number_of_active_dpp_per_ratio[j] + v->dpp_per_plane_per_ratio[j][k];
		}
	}
	if ((v->dispclk_dppclk_support_per_ratio[0] == dcn_bw_yes && v->dispclk_dppclk_support_per_ratio[1] == dcn_bw_no) || (v->dispclk_dppclk_support_per_ratio[0] == v->dispclk_dppclk_support_per_ratio[1] && (v->total_number_of_active_dpp_per_ratio[0] < v->total_number_of_active_dpp_per_ratio[1] || (((v->total_number_of_active_dpp_per_ratio[0] == v->total_number_of_active_dpp_per_ratio[1]) && v->required_dispclk_per_ratio[0] <= 0.5 * v->required_dispclk_per_ratio[1]))))) {
		v->dispclk_dppclk_ratio = 1;
		v->final_error_message = v->error_message[0];
	}
	else {
		v->dispclk_dppclk_ratio = 2;
		v->final_error_message = v->error_message[1];
	}
	for (k = 0; k <= v->number_of_active_planes - 1; k++) {
		v->dpp_per_plane[k] = v->dpp_per_plane_per_ratio[v->dispclk_dppclk_ratio - 1][k];
	}
	for (k = 0; k <= v->number_of_active_planes - 1; k++) {
		if (v->source_pixel_format[k] == dcn_bw_rgb_sub_64) {
			v->byte_per_pix_dety = 8.0;
			v->byte_per_pix_detc = 0.0;
		}
		else if (v->source_pixel_format[k] == dcn_bw_rgb_sub_32) {
			v->byte_per_pix_dety = 4.0;
			v->byte_per_pix_detc = 0.0;
		}
		else if (v->source_pixel_format[k] == dcn_bw_rgb_sub_16) {
			v->byte_per_pix_dety = 2.0;
			v->byte_per_pix_detc = 0.0;
		}
		else if (v->source_pixel_format[k] == dcn_bw_yuv420_sub_8) {
			v->byte_per_pix_dety = 1.0;
			v->byte_per_pix_detc = 2.0;
		}
		else {
			v->byte_per_pix_dety = 4.0f / 3.0f;
			v->byte_per_pix_detc = 8.0f / 3.0f;
		}
		if ((v->source_pixel_format[k] == dcn_bw_rgb_sub_64 || v->source_pixel_format[k] == dcn_bw_rgb_sub_32 || v->source_pixel_format[k] == dcn_bw_rgb_sub_16)) {
			if (v->source_surface_mode[k] == dcn_bw_sw_linear) {
				v->read256_bytes_block_height_y = 1.0;
			}
			else if (v->source_pixel_format[k] == dcn_bw_rgb_sub_64) {
				v->read256_bytes_block_height_y = 4.0;
			}
			else {
				v->read256_bytes_block_height_y = 8.0;
			}
			v->read256_bytes_block_width_y = 256.0 /dcn_bw_ceil2(v->byte_per_pix_dety, 1.0) / v->read256_bytes_block_height_y;
			v->read256_bytes_block_height_c = 0.0;
			v->read256_bytes_block_width_c = 0.0;
		}
		else {
			if (v->source_surface_mode[k] == dcn_bw_sw_linear) {
				v->read256_bytes_block_height_y = 1.0;
				v->read256_bytes_block_height_c = 1.0;
			}
			else if (v->source_pixel_format[k] == dcn_bw_yuv420_sub_8) {
				v->read256_bytes_block_height_y = 16.0;
				v->read256_bytes_block_height_c = 8.0;
			}
			else {
				v->read256_bytes_block_height_y = 8.0;
				v->read256_bytes_block_height_c = 8.0;
			}
			v->read256_bytes_block_width_y = 256.0 /dcn_bw_ceil2(v->byte_per_pix_dety, 1.0) / v->read256_bytes_block_height_y;
			v->read256_bytes_block_width_c = 256.0 /dcn_bw_ceil2(v->byte_per_pix_detc, 2.0) / v->read256_bytes_block_height_c;
		}
		if (v->source_scan[k] == dcn_bw_hor) {
			v->maximum_swath_height_y = v->read256_bytes_block_height_y;
			v->maximum_swath_height_c = v->read256_bytes_block_height_c;
		}
		else {
			v->maximum_swath_height_y = v->read256_bytes_block_width_y;
			v->maximum_swath_height_c = v->read256_bytes_block_width_c;
		}
		if ((v->source_pixel_format[k] == dcn_bw_rgb_sub_64 || v->source_pixel_format[k] == dcn_bw_rgb_sub_32 || v->source_pixel_format[k] == dcn_bw_rgb_sub_16)) {
			if (v->source_surface_mode[k] == dcn_bw_sw_linear || (v->source_pixel_format[k] == dcn_bw_rgb_sub_64 && (v->source_surface_mode[k] == dcn_bw_sw_4_kb_s || v->source_surface_mode[k] == dcn_bw_sw_4_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_var_s || v->source_surface_mode[k] == dcn_bw_sw_var_s_x) && v->source_scan[k] == dcn_bw_hor)) {
				v->minimum_swath_height_y = v->maximum_swath_height_y;
			}
			else {
				v->minimum_swath_height_y = v->maximum_swath_height_y / 2.0;
			}
			v->minimum_swath_height_c = v->maximum_swath_height_c;
		}
		else {
			if (v->source_surface_mode[k] == dcn_bw_sw_linear) {
				v->minimum_swath_height_y = v->maximum_swath_height_y;
				v->minimum_swath_height_c = v->maximum_swath_height_c;
			}
			else if (v->source_pixel_format[k] == dcn_bw_yuv420_sub_8 && v->source_scan[k] == dcn_bw_hor) {
				v->minimum_swath_height_y = v->maximum_swath_height_y / 2.0;
				if (v->bug_forcing_luma_and_chroma_request_to_same_size_fixed == dcn_bw_yes) {
					v->minimum_swath_height_c = v->maximum_swath_height_c;
				}
				else {
					v->minimum_swath_height_c = v->maximum_swath_height_c / 2.0;
				}
			}
			else if (v->source_pixel_format[k] == dcn_bw_yuv420_sub_10 && v->source_scan[k] == dcn_bw_hor) {
				v->minimum_swath_height_c = v->maximum_swath_height_c / 2.0;
				if (v->bug_forcing_luma_and_chroma_request_to_same_size_fixed == dcn_bw_yes) {
					v->minimum_swath_height_y = v->maximum_swath_height_y;
				}
				else {
					v->minimum_swath_height_y = v->maximum_swath_height_y / 2.0;
				}
			}
			else {
				v->minimum_swath_height_y = v->maximum_swath_height_y;
				v->minimum_swath_height_c = v->maximum_swath_height_c;
			}
		}
		if (v->source_scan[k] == dcn_bw_hor) {
			v->swath_width = v->viewport_width[k] / v->dpp_per_plane[k];
		}
		else {
			v->swath_width = v->viewport_height[k] / v->dpp_per_plane[k];
		}
		v->swath_width_granularity_y = 256.0 /dcn_bw_ceil2(v->byte_per_pix_dety, 1.0) / v->maximum_swath_height_y;
		v->rounded_up_max_swath_size_bytes_y = (dcn_bw_ceil2(v->swath_width - 1.0, v->swath_width_granularity_y) + v->swath_width_granularity_y) * v->byte_per_pix_dety * v->maximum_swath_height_y;
		if (v->source_pixel_format[k] == dcn_bw_yuv420_sub_10) {
			v->rounded_up_max_swath_size_bytes_y =dcn_bw_ceil2(v->rounded_up_max_swath_size_bytes_y, 256.0) + 256;
		}
		if (v->maximum_swath_height_c > 0.0) {
			v->swath_width_granularity_c = 256.0 /dcn_bw_ceil2(v->byte_per_pix_detc, 2.0) / v->maximum_swath_height_c;
		}
		v->rounded_up_max_swath_size_bytes_c = (dcn_bw_ceil2(v->swath_width / 2.0 - 1.0, v->swath_width_granularity_c) + v->swath_width_granularity_c) * v->byte_per_pix_detc * v->maximum_swath_height_c;
		if (v->source_pixel_format[k] == dcn_bw_yuv420_sub_10) {
			v->rounded_up_max_swath_size_bytes_c =dcn_bw_ceil2(v->rounded_up_max_swath_size_bytes_c, 256.0) + 256;
		}
		if (v->rounded_up_max_swath_size_bytes_y + v->rounded_up_max_swath_size_bytes_c <= v->det_buffer_size_in_kbyte * 1024.0 / 2.0) {
			v->swath_height_y[k] = v->maximum_swath_height_y;
			v->swath_height_c[k] = v->maximum_swath_height_c;
		}
		else {
			v->swath_height_y[k] = v->minimum_swath_height_y;
			v->swath_height_c[k] = v->minimum_swath_height_c;
		}
		if (v->swath_height_c[k] == 0.0) {
			v->det_buffer_size_y[k] = v->det_buffer_size_in_kbyte * 1024.0;
			v->det_buffer_size_c[k] = 0.0;
		}
		else if (v->swath_height_y[k] <= v->swath_height_c[k]) {
			v->det_buffer_size_y[k] = v->det_buffer_size_in_kbyte * 1024.0 / 2.0;
			v->det_buffer_size_c[k] = v->det_buffer_size_in_kbyte * 1024.0 / 2.0;
		}
		else {
			v->det_buffer_size_y[k] = v->det_buffer_size_in_kbyte * 1024.0 * 2.0 / 3.0;
			v->det_buffer_size_c[k] = v->det_buffer_size_in_kbyte * 1024.0 / 3.0;
		}
	}
}