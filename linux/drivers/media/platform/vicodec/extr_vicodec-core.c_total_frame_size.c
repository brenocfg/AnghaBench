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
struct vicodec_q_data {unsigned int coded_width; unsigned int coded_height; TYPE_1__* info; } ;
struct TYPE_2__ {unsigned int width_div; unsigned int height_div; int components_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static unsigned int total_frame_size(struct vicodec_q_data *q_data)
{
	unsigned int size;
	unsigned int chroma_div;

	if (!q_data->info) {
		WARN_ON(1);
		return 0;
	}
	size = q_data->coded_width * q_data->coded_height;
	chroma_div = q_data->info->width_div * q_data->info->height_div;

	if (q_data->info->components_num == 4)
		return 2 * size + 2 * (size / chroma_div);
	else if (q_data->info->components_num == 3)
		return size + 2 * (size / chroma_div);
	return size;
}