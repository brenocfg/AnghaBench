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
struct TYPE_2__ {int* b_valid; } ;
struct qed_hwfn {TYPE_1__ rt_data; } ;

/* Variables and functions */
 int RUNTIME_ARRAY_SIZE ; 

void qed_init_clear_rt_data(struct qed_hwfn *p_hwfn)
{
	int i;

	for (i = 0; i < RUNTIME_ARRAY_SIZE; i++)
		p_hwfn->rt_data.b_valid[i] = false;
}