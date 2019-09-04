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
struct sys_reg_params {scalar_t__ is_write; int /*<<< orphan*/  Op2; int /*<<< orphan*/  CRm; int /*<<< orphan*/  CRn; int /*<<< orphan*/  Op1; int /*<<< orphan*/  Op0; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_pr_unimpl (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void print_sys_reg_instr(const struct sys_reg_params *p)
{
	/* Look, we even formatted it for you to paste into the table! */
	kvm_pr_unimpl(" { Op0(%2u), Op1(%2u), CRn(%2u), CRm(%2u), Op2(%2u), func_%s },\n",
		      p->Op0, p->Op1, p->CRn, p->CRm, p->Op2, p->is_write ? "write" : "read");
}