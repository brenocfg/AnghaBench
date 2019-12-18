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
struct pch_can_priv {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  srst; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pch_can_reset(struct pch_can_priv *priv)
{
	/* write to sw reset register */
	iowrite32(1, &priv->regs->srst);
	iowrite32(0, &priv->regs->srst);
}