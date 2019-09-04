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
struct hclge_desc {scalar_t__* data; } ;

/* Variables and functions */

__attribute__((used)) static bool hclge_is_all_function_id_zero(struct hclge_desc *desc)
{
#define HCLGE_DESC_NUMBER 3
#define HCLGE_FUNC_NUMBER_PER_DESC 6
	int i, j;

	for (i = 1; i < HCLGE_DESC_NUMBER; i++)
		for (j = 0; j < HCLGE_FUNC_NUMBER_PER_DESC; j++)
			if (desc[i].data[j])
				return false;

	return true;
}