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
struct ib_sge {scalar_t__ length; } ;

/* Variables and functions */

__attribute__((used)) static int sge_data_len(struct ib_sge *sg_list, int num_sge)
{
	int i, len = 0;

	for (i = 0; i < num_sge; i++)
		len += sg_list[i].length;

	return len;
}