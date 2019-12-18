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
struct ib_sge {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; int /*<<< orphan*/  lkey; } ;
struct hns_roce_v2_wqe_data_seg {void* len; int /*<<< orphan*/  addr; void* lkey; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_data_seg_v2(struct hns_roce_v2_wqe_data_seg *dseg,
			    struct ib_sge *sg)
{
	dseg->lkey = cpu_to_le32(sg->lkey);
	dseg->addr = cpu_to_le64(sg->addr);
	dseg->len  = cpu_to_le32(sg->length);
}