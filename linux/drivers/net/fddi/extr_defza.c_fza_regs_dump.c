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
struct fza_private {TYPE_1__* regs; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  control_b; int /*<<< orphan*/  control_a; int /*<<< orphan*/  int_mask; int /*<<< orphan*/  status; int /*<<< orphan*/  int_event; int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readw_o (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readw_u (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fza_regs_dump(struct fza_private *fp)
{
	pr_debug("%s: iomem registers:\n", fp->name);
	pr_debug(" reset:           0x%04x\n", readw_o(&fp->regs->reset));
	pr_debug(" interrupt event: 0x%04x\n", readw_u(&fp->regs->int_event));
	pr_debug(" status:          0x%04x\n", readw_u(&fp->regs->status));
	pr_debug(" interrupt mask:  0x%04x\n", readw_u(&fp->regs->int_mask));
	pr_debug(" control A:       0x%04x\n", readw_u(&fp->regs->control_a));
	pr_debug(" control B:       0x%04x\n", readw_u(&fp->regs->control_b));
}