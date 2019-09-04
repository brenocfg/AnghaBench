#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct vop_reg {int dummy; } ;
struct vop {TYPE_1__* data; } ;
struct TYPE_4__ {size_t nintrs; int* intrs; } ;
struct TYPE_3__ {TYPE_2__* intr; } ;

/* Variables and functions */
 size_t vop_read_reg (struct vop*,int /*<<< orphan*/ ,struct vop_reg const*) ; 

__attribute__((used)) static inline uint32_t vop_get_intr_type(struct vop *vop,
					 const struct vop_reg *reg, int type)
{
	uint32_t i, ret = 0;
	uint32_t regs = vop_read_reg(vop, 0, reg);

	for (i = 0; i < vop->data->intr->nintrs; i++) {
		if ((type & vop->data->intr->intrs[i]) && (regs & 1 << i))
			ret |= vop->data->intr->intrs[i];
	}

	return ret;
}