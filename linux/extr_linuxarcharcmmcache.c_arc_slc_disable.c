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

/* Variables and functions */
 int ARC_REG_SLC_CTRL ; 
 int /*<<< orphan*/  OP_FLUSH_N_INV ; 
 int SLC_CTRL_DIS ; 
 int read_aux_reg (int const) ; 
 int /*<<< orphan*/  slc_entire_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_aux_reg (int const,int) ; 

__attribute__((used)) static inline void arc_slc_disable(void)
{
	const int r = ARC_REG_SLC_CTRL;

	slc_entire_op(OP_FLUSH_N_INV);
	write_aux_reg(r, read_aux_reg(r) | SLC_CTRL_DIS);
}