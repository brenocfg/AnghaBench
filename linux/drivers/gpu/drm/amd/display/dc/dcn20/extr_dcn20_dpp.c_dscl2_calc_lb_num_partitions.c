#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ alpha_en; } ;
struct TYPE_7__ {int width; } ;
struct TYPE_6__ {int width; } ;
struct TYPE_5__ {int width; } ;
struct scaler_data {TYPE_4__ lb_params; TYPE_3__ recout; TYPE_2__ viewport_c; TYPE_1__ viewport; } ;
typedef  enum lb_memory_config { ____Placeholder_lb_memory_config } lb_memory_config ;

/* Variables and functions */
 int LB_MEMORY_CONFIG_1 ; 
 int LB_MEMORY_CONFIG_2 ; 
 int LB_MEMORY_CONFIG_3 ; 

void dscl2_calc_lb_num_partitions(
		const struct scaler_data *scl_data,
		enum lb_memory_config lb_config,
		int *num_part_y,
		int *num_part_c)
{
	int memory_line_size_y, memory_line_size_c, memory_line_size_a,
	lb_memory_size, lb_memory_size_c, lb_memory_size_a, num_partitions_a;

	int line_size = scl_data->viewport.width < scl_data->recout.width ?
			scl_data->viewport.width : scl_data->recout.width;
	int line_size_c = scl_data->viewport_c.width < scl_data->recout.width ?
			scl_data->viewport_c.width : scl_data->recout.width;

	if (line_size == 0)
		line_size = 1;

	if (line_size_c == 0)
		line_size_c = 1;

	memory_line_size_y = (line_size + 5) / 6; /* +5 to ceil */
	memory_line_size_c = (line_size_c + 5) / 6; /* +5 to ceil */
	memory_line_size_a = (line_size + 5) / 6; /* +5 to ceil */

	if (lb_config == LB_MEMORY_CONFIG_1) {
		lb_memory_size = 970;
		lb_memory_size_c = 970;
		lb_memory_size_a = 970;
	} else if (lb_config == LB_MEMORY_CONFIG_2) {
		lb_memory_size = 1290;
		lb_memory_size_c = 1290;
		lb_memory_size_a = 1290;
	} else if (lb_config == LB_MEMORY_CONFIG_3) {
		/* 420 mode: using 3rd mem from Y, Cr and Cb */
		lb_memory_size = 970 + 1290 + 484 + 484 + 484;
		lb_memory_size_c = 970 + 1290;
		lb_memory_size_a = 970 + 1290 + 484;
	} else {
		lb_memory_size = 970 + 1290 + 484;
		lb_memory_size_c = 970 + 1290 + 484;
		lb_memory_size_a = 970 + 1290 + 484;
	}
	*num_part_y = lb_memory_size / memory_line_size_y;
	*num_part_c = lb_memory_size_c / memory_line_size_c;
	num_partitions_a = lb_memory_size_a / memory_line_size_a;

	if (scl_data->lb_params.alpha_en
			&& (num_partitions_a < *num_part_y))
		*num_part_y = num_partitions_a;

	if (*num_part_y > 64)
		*num_part_y = 64;
	if (*num_part_c > 64)
		*num_part_c = 64;
}