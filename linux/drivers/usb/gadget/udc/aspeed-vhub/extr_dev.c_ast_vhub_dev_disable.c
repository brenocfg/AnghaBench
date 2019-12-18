#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  speed; } ;
struct ast_vhub_dev {int enabled; int index; TYPE_1__ gadget; scalar_t__ regs; TYPE_2__* vhub; } ;
struct TYPE_4__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ AST_VHUB_DEV_EN_CTRL ; 
 scalar_t__ AST_VHUB_IER ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int VHUB_IRQ_DEVICE1 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ast_vhub_dev_disable(struct ast_vhub_dev *d)
{
	u32 reg, hmsk;

	if (!d->enabled)
		return;

	/* Disable device interrupt in the hub */
	hmsk = VHUB_IRQ_DEVICE1 << d->index;
	reg = readl(d->vhub->regs + AST_VHUB_IER);
	reg &= ~hmsk;
	writel(reg, d->vhub->regs + AST_VHUB_IER);

	/* Then disable device */
	writel(0, d->regs + AST_VHUB_DEV_EN_CTRL);
	d->gadget.speed = USB_SPEED_UNKNOWN;
	d->enabled = false;
}