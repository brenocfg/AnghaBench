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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ext_irq_cfg_reg1 ; 
 int /*<<< orphan*/  ext_irq_cfg_reg2 ; 

__attribute__((used)) static inline u32 get_ext_irq_perf_reg(int irq)
{
	if (irq < 4)
		return ext_irq_cfg_reg1;
	return ext_irq_cfg_reg2;
}