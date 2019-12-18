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
typedef  int u32 ;
struct pch_can_priv {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int ioread32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 pch_can_int_pending(struct pch_can_priv *priv)
{
	return ioread32(&priv->regs->intr) & 0xffff;
}