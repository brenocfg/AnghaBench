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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int ctrlmode; } ;
struct pch_can_priv {TYPE_2__* regs; TYPE_1__ can; } ;
struct TYPE_4__ {int /*<<< orphan*/  opt; int /*<<< orphan*/  cont; } ;

/* Variables and functions */
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int /*<<< orphan*/  PCH_CTRL_OPT ; 
 int /*<<< orphan*/  PCH_OPT_LBACK ; 
 int /*<<< orphan*/  PCH_OPT_SILENT ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pch_can_bit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_can_set_optmode(struct pch_can_priv *priv)
{
	u32 reg_val = ioread32(&priv->regs->opt);

	if (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		reg_val |= PCH_OPT_SILENT;

	if (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		reg_val |= PCH_OPT_LBACK;

	pch_can_bit_set(&priv->regs->cont, PCH_CTRL_OPT);
	iowrite32(reg_val, &priv->regs->opt);
}