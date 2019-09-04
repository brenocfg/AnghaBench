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
struct x86_emulate_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_REGS_RSP ; 
 int /*<<< orphan*/  masked_increment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_rmw (struct x86_emulate_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_mask (struct x86_emulate_ctxt*) ; 

__attribute__((used)) static void rsp_increment(struct x86_emulate_ctxt *ctxt, int inc)
{
	masked_increment(reg_rmw(ctxt, VCPU_REGS_RSP), stack_mask(ctxt), inc);
}