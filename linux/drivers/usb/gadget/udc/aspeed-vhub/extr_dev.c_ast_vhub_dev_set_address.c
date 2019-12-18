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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ast_vhub_dev {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ AST_VHUB_DEV_EN_CTRL ; 
 int /*<<< orphan*/  DDBG (struct ast_vhub_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VHUB_DEV_EN_ADDR_MASK ; 
 int /*<<< orphan*/  VHUB_DEV_EN_SET_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ast_vhub_dev_set_address(struct ast_vhub_dev *d, u8 addr)
{
	u32 reg;

	DDBG(d, "SET_ADDRESS: Got address %x\n", addr);

	reg = readl(d->regs + AST_VHUB_DEV_EN_CTRL);
	reg &= ~VHUB_DEV_EN_ADDR_MASK;
	reg |= VHUB_DEV_EN_SET_ADDR(addr);
	writel(reg, d->regs + AST_VHUB_DEV_EN_CTRL);
}