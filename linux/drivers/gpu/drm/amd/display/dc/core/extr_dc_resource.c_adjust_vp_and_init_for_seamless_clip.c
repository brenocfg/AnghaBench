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
struct fixed31_32 {int value; } ;

/* Variables and functions */
 struct fixed31_32 dc_fixpt_add (struct fixed31_32,int /*<<< orphan*/ ) ; 
 struct fixed31_32 dc_fixpt_add_int (struct fixed31_32,int) ; 
 int dc_fixpt_floor (struct fixed31_32) ; 
 int /*<<< orphan*/  dc_fixpt_mul_int (struct fixed31_32,int) ; 
 struct fixed31_32 dc_fixpt_sub (struct fixed31_32,struct fixed31_32) ; 

__attribute__((used)) static inline void adjust_vp_and_init_for_seamless_clip(
		bool flip_scan_dir,
		int recout_skip,
		int src_size,
		int taps,
		struct fixed31_32 ratio,
		struct fixed31_32 *init,
		int *vp_offset,
		int *vp_size)
{
	if (!flip_scan_dir) {
		/* Adjust for viewport end clip-off */
		if ((*vp_offset + *vp_size) < src_size) {
			int vp_clip = src_size - *vp_size - *vp_offset;
			int int_part = dc_fixpt_floor(dc_fixpt_sub(*init, ratio));

			int_part = int_part > 0 ? int_part : 0;
			*vp_size += int_part < vp_clip ? int_part : vp_clip;
		}

		/* Adjust for non-0 viewport offset */
		if (*vp_offset) {
			int int_part;

			*init = dc_fixpt_add(*init, dc_fixpt_mul_int(ratio, recout_skip));
			int_part = dc_fixpt_floor(*init) - *vp_offset;
			if (int_part < taps) {
				int int_adj = *vp_offset >= (taps - int_part) ?
							(taps - int_part) : *vp_offset;
				*vp_offset -= int_adj;
				*vp_size += int_adj;
				int_part += int_adj;
			} else if (int_part > taps) {
				*vp_offset += int_part - taps;
				*vp_size -= int_part - taps;
				int_part = taps;
			}
			init->value &= 0xffffffff;
			*init = dc_fixpt_add_int(*init, int_part);
		}
	} else {
		/* Adjust for non-0 viewport offset */
		if (*vp_offset) {
			int int_part = dc_fixpt_floor(dc_fixpt_sub(*init, ratio));

			int_part = int_part > 0 ? int_part : 0;
			*vp_size += int_part < *vp_offset ? int_part : *vp_offset;
			*vp_offset -= int_part < *vp_offset ? int_part : *vp_offset;
		}

		/* Adjust for viewport end clip-off */
		if ((*vp_offset + *vp_size) < src_size) {
			int int_part;
			int end_offset = src_size - *vp_offset - *vp_size;

			/*
			 * this is init if vp had no offset, keep in mind this is from the
			 * right side of vp due to scan direction
			 */
			*init = dc_fixpt_add(*init, dc_fixpt_mul_int(ratio, recout_skip));
			/*
			 * this is the difference between first pixel of viewport available to read
			 * and init position, takning into account scan direction
			 */
			int_part = dc_fixpt_floor(*init) - end_offset;
			if (int_part < taps) {
				int int_adj = end_offset >= (taps - int_part) ?
							(taps - int_part) : end_offset;
				*vp_size += int_adj;
				int_part += int_adj;
			} else if (int_part > taps) {
				*vp_size += int_part - taps;
				int_part = taps;
			}
			init->value &= 0xffffffff;
			*init = dc_fixpt_add_int(*init, int_part);
		}
	}
}