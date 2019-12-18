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
struct iram_table_v_2_2 {int flags; int* deviation_gain; int** bright_pos_gain; int** dark_pos_gain; int* hybrid_factor; int* contrast_factor; int* iir_curve; void** crgb_slope; void** crgb_offset; void** crgb_thresh; void*** max_reduction; void*** min_reduction; } ;
struct dmcu_iram_parameters {unsigned int set; } ;

/* Variables and functions */
 size_t** abm_config ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  fill_backlight_transform_table_v_2_2 (struct dmcu_iram_parameters,struct iram_table_v_2_2*) ; 
 void** max_reduction_table_v_2_2 ; 
 void** min_reduction_table_v_2_2 ; 

void fill_iram_v_2_2(struct iram_table_v_2_2 *ram_table, struct dmcu_iram_parameters params)
{
	unsigned int set = params.set;

	ram_table->flags = 0x0;

	ram_table->deviation_gain[0] = 0xb3;
	ram_table->deviation_gain[1] = 0xa8;
	ram_table->deviation_gain[2] = 0x98;
	ram_table->deviation_gain[3] = 0x68;

	ram_table->min_reduction[0][0] = min_reduction_table_v_2_2[abm_config[set][0]];
	ram_table->min_reduction[1][0] = min_reduction_table_v_2_2[abm_config[set][0]];
	ram_table->min_reduction[2][0] = min_reduction_table_v_2_2[abm_config[set][0]];
	ram_table->min_reduction[3][0] = min_reduction_table_v_2_2[abm_config[set][0]];
	ram_table->min_reduction[4][0] = min_reduction_table_v_2_2[abm_config[set][0]];
	ram_table->max_reduction[0][0] = max_reduction_table_v_2_2[abm_config[set][0]];
	ram_table->max_reduction[1][0] = max_reduction_table_v_2_2[abm_config[set][0]];
	ram_table->max_reduction[2][0] = max_reduction_table_v_2_2[abm_config[set][0]];
	ram_table->max_reduction[3][0] = max_reduction_table_v_2_2[abm_config[set][0]];
	ram_table->max_reduction[4][0] = max_reduction_table_v_2_2[abm_config[set][0]];

	ram_table->min_reduction[0][1] = min_reduction_table_v_2_2[abm_config[set][1]];
	ram_table->min_reduction[1][1] = min_reduction_table_v_2_2[abm_config[set][1]];
	ram_table->min_reduction[2][1] = min_reduction_table_v_2_2[abm_config[set][1]];
	ram_table->min_reduction[3][1] = min_reduction_table_v_2_2[abm_config[set][1]];
	ram_table->min_reduction[4][1] = min_reduction_table_v_2_2[abm_config[set][1]];
	ram_table->max_reduction[0][1] = max_reduction_table_v_2_2[abm_config[set][1]];
	ram_table->max_reduction[1][1] = max_reduction_table_v_2_2[abm_config[set][1]];
	ram_table->max_reduction[2][1] = max_reduction_table_v_2_2[abm_config[set][1]];
	ram_table->max_reduction[3][1] = max_reduction_table_v_2_2[abm_config[set][1]];
	ram_table->max_reduction[4][1] = max_reduction_table_v_2_2[abm_config[set][1]];

	ram_table->min_reduction[0][2] = min_reduction_table_v_2_2[abm_config[set][2]];
	ram_table->min_reduction[1][2] = min_reduction_table_v_2_2[abm_config[set][2]];
	ram_table->min_reduction[2][2] = min_reduction_table_v_2_2[abm_config[set][2]];
	ram_table->min_reduction[3][2] = min_reduction_table_v_2_2[abm_config[set][2]];
	ram_table->min_reduction[4][2] = min_reduction_table_v_2_2[abm_config[set][2]];
	ram_table->max_reduction[0][2] = max_reduction_table_v_2_2[abm_config[set][2]];
	ram_table->max_reduction[1][2] = max_reduction_table_v_2_2[abm_config[set][2]];
	ram_table->max_reduction[2][2] = max_reduction_table_v_2_2[abm_config[set][2]];
	ram_table->max_reduction[3][2] = max_reduction_table_v_2_2[abm_config[set][2]];
	ram_table->max_reduction[4][2] = max_reduction_table_v_2_2[abm_config[set][2]];

	ram_table->min_reduction[0][3] = min_reduction_table_v_2_2[abm_config[set][3]];
	ram_table->min_reduction[1][3] = min_reduction_table_v_2_2[abm_config[set][3]];
	ram_table->min_reduction[2][3] = min_reduction_table_v_2_2[abm_config[set][3]];
	ram_table->min_reduction[3][3] = min_reduction_table_v_2_2[abm_config[set][3]];
	ram_table->min_reduction[4][3] = min_reduction_table_v_2_2[abm_config[set][3]];
	ram_table->max_reduction[0][3] = max_reduction_table_v_2_2[abm_config[set][3]];
	ram_table->max_reduction[1][3] = max_reduction_table_v_2_2[abm_config[set][3]];
	ram_table->max_reduction[2][3] = max_reduction_table_v_2_2[abm_config[set][3]];
	ram_table->max_reduction[3][3] = max_reduction_table_v_2_2[abm_config[set][3]];
	ram_table->max_reduction[4][3] = max_reduction_table_v_2_2[abm_config[set][3]];

	ram_table->bright_pos_gain[0][0] = 0x20;
	ram_table->bright_pos_gain[0][1] = 0x20;
	ram_table->bright_pos_gain[0][2] = 0x20;
	ram_table->bright_pos_gain[0][3] = 0x20;
	ram_table->bright_pos_gain[1][0] = 0x20;
	ram_table->bright_pos_gain[1][1] = 0x20;
	ram_table->bright_pos_gain[1][2] = 0x20;
	ram_table->bright_pos_gain[1][3] = 0x20;
	ram_table->bright_pos_gain[2][0] = 0x20;
	ram_table->bright_pos_gain[2][1] = 0x20;
	ram_table->bright_pos_gain[2][2] = 0x20;
	ram_table->bright_pos_gain[2][3] = 0x20;
	ram_table->bright_pos_gain[3][0] = 0x20;
	ram_table->bright_pos_gain[3][1] = 0x20;
	ram_table->bright_pos_gain[3][2] = 0x20;
	ram_table->bright_pos_gain[3][3] = 0x20;
	ram_table->bright_pos_gain[4][0] = 0x20;
	ram_table->bright_pos_gain[4][1] = 0x20;
	ram_table->bright_pos_gain[4][2] = 0x20;
	ram_table->bright_pos_gain[4][3] = 0x20;

	ram_table->dark_pos_gain[0][0] = 0x00;
	ram_table->dark_pos_gain[0][1] = 0x00;
	ram_table->dark_pos_gain[0][2] = 0x00;
	ram_table->dark_pos_gain[0][3] = 0x00;
	ram_table->dark_pos_gain[1][0] = 0x00;
	ram_table->dark_pos_gain[1][1] = 0x00;
	ram_table->dark_pos_gain[1][2] = 0x00;
	ram_table->dark_pos_gain[1][3] = 0x00;
	ram_table->dark_pos_gain[2][0] = 0x00;
	ram_table->dark_pos_gain[2][1] = 0x00;
	ram_table->dark_pos_gain[2][2] = 0x00;
	ram_table->dark_pos_gain[2][3] = 0x00;
	ram_table->dark_pos_gain[3][0] = 0x00;
	ram_table->dark_pos_gain[3][1] = 0x00;
	ram_table->dark_pos_gain[3][2] = 0x00;
	ram_table->dark_pos_gain[3][3] = 0x00;
	ram_table->dark_pos_gain[4][0] = 0x00;
	ram_table->dark_pos_gain[4][1] = 0x00;
	ram_table->dark_pos_gain[4][2] = 0x00;
	ram_table->dark_pos_gain[4][3] = 0x00;

	ram_table->hybrid_factor[0] = 0xff;
	ram_table->hybrid_factor[1] = 0xff;
	ram_table->hybrid_factor[2] = 0xff;
	ram_table->hybrid_factor[3] = 0xc0;

	ram_table->contrast_factor[0] = 0x99;
	ram_table->contrast_factor[1] = 0x99;
	ram_table->contrast_factor[2] = 0x90;
	ram_table->contrast_factor[3] = 0x80;

	ram_table->iir_curve[0] = 0x65;
	ram_table->iir_curve[1] = 0x65;
	ram_table->iir_curve[2] = 0x65;
	ram_table->iir_curve[3] = 0x65;
	ram_table->iir_curve[4] = 0x65;

	//Gamma 2.2
	ram_table->crgb_thresh[0] = cpu_to_be16(0x127c);
	ram_table->crgb_thresh[1] = cpu_to_be16(0x151b);
	ram_table->crgb_thresh[2] = cpu_to_be16(0x17d5);
	ram_table->crgb_thresh[3] = cpu_to_be16(0x1a56);
	ram_table->crgb_thresh[4] = cpu_to_be16(0x1c83);
	ram_table->crgb_thresh[5] = cpu_to_be16(0x1e72);
	ram_table->crgb_thresh[6] = cpu_to_be16(0x20f0);
	ram_table->crgb_thresh[7] = cpu_to_be16(0x232b);
	ram_table->crgb_offset[0] = cpu_to_be16(0x2999);
	ram_table->crgb_offset[1] = cpu_to_be16(0x3999);
	ram_table->crgb_offset[2] = cpu_to_be16(0x4666);
	ram_table->crgb_offset[3] = cpu_to_be16(0x5999);
	ram_table->crgb_offset[4] = cpu_to_be16(0x6333);
	ram_table->crgb_offset[5] = cpu_to_be16(0x7800);
	ram_table->crgb_offset[6] = cpu_to_be16(0x8c00);
	ram_table->crgb_offset[7] = cpu_to_be16(0xa000);
	ram_table->crgb_slope[0]  = cpu_to_be16(0x3609);
	ram_table->crgb_slope[1]  = cpu_to_be16(0x2dfa);
	ram_table->crgb_slope[2]  = cpu_to_be16(0x27ea);
	ram_table->crgb_slope[3]  = cpu_to_be16(0x235d);
	ram_table->crgb_slope[4]  = cpu_to_be16(0x2042);
	ram_table->crgb_slope[5]  = cpu_to_be16(0x1dc3);
	ram_table->crgb_slope[6]  = cpu_to_be16(0x1b1a);
	ram_table->crgb_slope[7]  = cpu_to_be16(0x1910);

	fill_backlight_transform_table_v_2_2(
			params, ram_table);
}