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
typedef  int /*<<< orphan*/  u64 ;
typedef  void* u32 ;
struct genwqe_reg {int /*<<< orphan*/  val; void* idx; void* addr; } ;
struct genwqe_dev {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

__attribute__((used)) static int set_reg_idx(struct genwqe_dev *cd, struct genwqe_reg *r,
		       unsigned int *i, unsigned int m, u32 addr, u32 idx,
		       u64 val)
{
	if (WARN_ON_ONCE(*i >= m))
		return -EFAULT;

	r[*i].addr = addr;
	r[*i].idx = idx;
	r[*i].val = val;
	++*i;
	return 0;
}