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
typedef  int u32 ;
struct hns_roce_cq {int* set_ci_db; } ;

/* Variables and functions */

__attribute__((used)) static void hns_roce_v2_cq_set_ci(struct hns_roce_cq *hr_cq, u32 cons_index)
{
	*hr_cq->set_ci_db = cons_index & 0xffffff;
}