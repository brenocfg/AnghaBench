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
struct firmware {int* data; int size; } ;
struct cyapa_tsg_bin_image_data_record {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct cyapa_tsg_bin_image_data_record *
cyapa_get_image_record_data_num(const struct firmware *fw,
		int *record_num)
{
	int head_size;

	head_size = fw->data[0] + 1;
	*record_num = (fw->size - head_size) /
			sizeof(struct cyapa_tsg_bin_image_data_record);
	return (struct cyapa_tsg_bin_image_data_record *)&fw->data[head_size];
}