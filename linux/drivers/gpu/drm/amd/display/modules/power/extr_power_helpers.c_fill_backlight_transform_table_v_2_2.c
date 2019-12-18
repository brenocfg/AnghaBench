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
struct iram_table_v_2_2 {int* backlight_thresholds; void** backlight_offsets; } ;
struct dmcu_iram_parameters {int backlight_lut_array_size; void** backlight_lut_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* DIV_ROUNDUP (unsigned int,unsigned int) ; 
 unsigned int NUM_BL_CURVE_SEGS ; 
 void* cpu_to_be16 (void*) ; 

__attribute__((used)) static void fill_backlight_transform_table_v_2_2(struct dmcu_iram_parameters params,
		struct iram_table_v_2_2 *table)
{
	unsigned int i;
	unsigned int num_entries = NUM_BL_CURVE_SEGS;
	unsigned int lut_index;

	table->backlight_thresholds[0] = 0;
	table->backlight_offsets[0] = params.backlight_lut_array[0];
	table->backlight_thresholds[num_entries-1] = 0xFFFF;
	table->backlight_offsets[num_entries-1] =
		params.backlight_lut_array[params.backlight_lut_array_size - 1];

	/* Setup all brightness levels between 0% and 100% exclusive
	 * Fills brightness-to-backlight transform table. Backlight custom curve
	 * describes transform from brightness to backlight. It will be defined
	 * as set of thresholds and set of offsets, together, implying
	 * extrapolation of custom curve into 16 uniformly spanned linear
	 * segments.  Each threshold/offset represented by 16 bit entry in
	 * format U4.10.
	 */
	for (i = 1; i+1 < num_entries; i++) {
		lut_index = (params.backlight_lut_array_size - 1) * i / (num_entries - 1);
		ASSERT(lut_index < params.backlight_lut_array_size);

		table->backlight_thresholds[i] =
			cpu_to_be16(DIV_ROUNDUP((i * 65536), num_entries));
		table->backlight_offsets[i] =
			cpu_to_be16(params.backlight_lut_array[lut_index]);
	}
}