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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_regs_write_reg (struct pt_regs*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_w_reg(struct pt_regs *regs, int reg, u64 val)
{
	pt_regs_write_reg(regs, reg, lower_32_bits(val));
}