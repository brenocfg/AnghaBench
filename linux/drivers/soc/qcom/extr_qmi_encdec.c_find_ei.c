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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct qmi_elem_info {scalar_t__ data_type; scalar_t__ tlv_type; } ;

/* Variables and functions */
 scalar_t__ QMI_EOTI ; 

__attribute__((used)) static struct qmi_elem_info *find_ei(struct qmi_elem_info *ei_array,
				     u32 type)
{
	struct qmi_elem_info *temp_ei = ei_array;

	while (temp_ei->data_type != QMI_EOTI) {
		if (temp_ei->tlv_type == (u8)type)
			return temp_ei;
		temp_ei = temp_ei + 1;
	}

	return NULL;
}