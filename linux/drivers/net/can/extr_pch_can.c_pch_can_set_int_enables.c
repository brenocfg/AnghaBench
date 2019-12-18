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
struct pch_can_priv {int /*<<< orphan*/  ndev; TYPE_1__* regs; } ;
typedef  enum pch_can_mode { ____Placeholder_pch_can_mode } pch_can_mode ;
struct TYPE_2__ {int /*<<< orphan*/  cont; } ;

/* Variables and functions */
#define  PCH_CAN_ALL 130 
#define  PCH_CAN_DISABLE 129 
#define  PCH_CAN_NONE 128 
 int /*<<< orphan*/  PCH_CTRL_IE ; 
 int /*<<< orphan*/  PCH_CTRL_IE_SIE_EIE ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pch_can_bit_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_can_bit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_can_set_int_enables(struct pch_can_priv *priv,
				    enum pch_can_mode interrupt_no)
{
	switch (interrupt_no) {
	case PCH_CAN_DISABLE:
		pch_can_bit_clear(&priv->regs->cont, PCH_CTRL_IE);
		break;

	case PCH_CAN_ALL:
		pch_can_bit_set(&priv->regs->cont, PCH_CTRL_IE_SIE_EIE);
		break;

	case PCH_CAN_NONE:
		pch_can_bit_clear(&priv->regs->cont, PCH_CTRL_IE_SIE_EIE);
		break;

	default:
		netdev_err(priv->ndev, "Invalid interrupt number.\n");
		break;
	}
}