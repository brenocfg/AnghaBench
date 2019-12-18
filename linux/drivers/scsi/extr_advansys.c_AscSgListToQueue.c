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

/* Variables and functions */
 int ASC_SG_LIST_PER_Q ; 

__attribute__((used)) static int AscSgListToQueue(int sg_list)
{
	int n_sg_list_qs;

	n_sg_list_qs = ((sg_list - 1) / ASC_SG_LIST_PER_Q);
	if (((sg_list - 1) % ASC_SG_LIST_PER_Q) != 0)
		n_sg_list_qs++;
	return n_sg_list_qs + 1;
}