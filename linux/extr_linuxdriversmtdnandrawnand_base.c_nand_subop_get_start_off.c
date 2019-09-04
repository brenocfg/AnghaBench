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
struct nand_subop {unsigned int first_instr_start_off; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int nand_subop_get_start_off(const struct nand_subop *subop,
					     unsigned int instr_idx)
{
	if (instr_idx)
		return 0;

	return subop->first_instr_start_off;
}