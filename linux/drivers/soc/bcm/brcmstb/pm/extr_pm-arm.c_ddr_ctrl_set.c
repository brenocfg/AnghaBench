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
typedef  int u32 ;
struct TYPE_4__ {int num_memc; scalar_t__ warm_boot_offset; TYPE_1__* memcs; } ;
struct TYPE_3__ {scalar_t__ ddr_ctrl; } ;

/* Variables and functions */
 TYPE_2__ ctrl ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static inline void ddr_ctrl_set(bool warmboot)
{
	int i;

	for (i = 0; i < ctrl.num_memc; i++) {
		u32 tmp;

		tmp = readl_relaxed(ctrl.memcs[i].ddr_ctrl +
				ctrl.warm_boot_offset);
		if (warmboot)
			tmp |= 1;
		else
			tmp &= ~1; /* Cold boot */
		writel_relaxed(tmp, ctrl.memcs[i].ddr_ctrl +
				ctrl.warm_boot_offset);
	}
	/* Complete sequence in order */
	wmb();
}