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
struct s5p_mfc_regs {int /*<<< orphan*/  risc2host_int; int /*<<< orphan*/  risc2host_command; } ;
struct s5p_mfc_dev {struct s5p_mfc_regs* mfc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_mfc_clear_int_flags_v6(struct s5p_mfc_dev *dev)
{
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	writel(0, mfc_regs->risc2host_command);
	writel(0, mfc_regs->risc2host_int);
}