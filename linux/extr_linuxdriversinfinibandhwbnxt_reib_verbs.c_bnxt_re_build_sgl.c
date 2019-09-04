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
struct ib_sge {scalar_t__ length; int /*<<< orphan*/  lkey; int /*<<< orphan*/  addr; } ;
struct bnxt_qplib_sge {scalar_t__ size; int /*<<< orphan*/  lkey; int /*<<< orphan*/  addr; } ;

/* Variables and functions */

__attribute__((used)) static int bnxt_re_build_sgl(struct ib_sge *ib_sg_list,
			     struct bnxt_qplib_sge *sg_list, int num)
{
	int i, total = 0;

	for (i = 0; i < num; i++) {
		sg_list[i].addr = ib_sg_list[i].addr;
		sg_list[i].lkey = ib_sg_list[i].lkey;
		sg_list[i].size = ib_sg_list[i].length;
		total += sg_list[i].size;
	}
	return total;
}