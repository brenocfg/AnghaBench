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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct its_node {scalar_t__ base; } ;
struct its_cmd_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ GITS_CREADR ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ its_cmd_ptr_to_offset (struct its_node*,struct its_cmd_block*) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int its_wait_for_range_completion(struct its_node *its,
					 struct its_cmd_block *from,
					 struct its_cmd_block *to)
{
	u64 rd_idx, from_idx, to_idx;
	u32 count = 1000000;	/* 1s! */

	from_idx = its_cmd_ptr_to_offset(its, from);
	to_idx = its_cmd_ptr_to_offset(its, to);

	while (1) {
		rd_idx = readl_relaxed(its->base + GITS_CREADR);

		/* Direct case */
		if (from_idx < to_idx && rd_idx >= to_idx)
			break;

		/* Wrapped case */
		if (from_idx >= to_idx && rd_idx >= to_idx && rd_idx < from_idx)
			break;

		count--;
		if (!count) {
			pr_err_ratelimited("ITS queue timeout (%llu %llu %llu)\n",
					   from_idx, to_idx, rd_idx);
			return -1;
		}
		cpu_relax();
		udelay(1);
	}

	return 0;
}