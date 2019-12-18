#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfp_prog {unsigned int subprog_cnt; TYPE_1__* subprog; } ;
struct TYPE_2__ {scalar_t__ needs_reg_push; } ;

/* Variables and functions */

__attribute__((used)) static bool nfp_prog_needs_callee_reg_save(struct nfp_prog *nfp_prog)
{
	unsigned int idx;

	for (idx = 1; idx < nfp_prog->subprog_cnt; idx++)
		if (nfp_prog->subprog[idx].needs_reg_push)
			return true;

	return false;
}