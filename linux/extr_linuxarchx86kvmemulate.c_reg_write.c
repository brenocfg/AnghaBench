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
typedef  int /*<<< orphan*/  ulong ;
struct x86_emulate_ctxt {int regs_valid; int regs_dirty; int /*<<< orphan*/ * _regs; } ;

/* Variables and functions */

__attribute__((used)) static ulong *reg_write(struct x86_emulate_ctxt *ctxt, unsigned nr)
{
	ctxt->regs_valid |= 1 << nr;
	ctxt->regs_dirty |= 1 << nr;
	return &ctxt->_regs[nr];
}