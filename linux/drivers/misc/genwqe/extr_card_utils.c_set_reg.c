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
typedef  int /*<<< orphan*/  u32 ;
struct genwqe_reg {int dummy; } ;
struct genwqe_dev {int dummy; } ;

/* Variables and functions */
 int set_reg_idx (struct genwqe_dev*,struct genwqe_reg*,unsigned int*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_reg(struct genwqe_dev *cd, struct genwqe_reg *r,
		   unsigned int *i, unsigned int m, u32 addr, u64 val)
{
	return set_reg_idx(cd, r, i, m, addr, 0, val);
}