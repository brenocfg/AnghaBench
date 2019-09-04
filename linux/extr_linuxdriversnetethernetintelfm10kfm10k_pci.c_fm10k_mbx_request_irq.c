#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* connect ) (struct fm10k_hw*,TYPE_3__*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct fm10k_hw {TYPE_3__ mbx; TYPE_1__ mac; } ;
struct fm10k_intfc {struct fm10k_hw hw; } ;

/* Variables and functions */
 scalar_t__ fm10k_mac_pf ; 
 int /*<<< orphan*/  fm10k_mbx_free_irq (struct fm10k_intfc*) ; 
 int fm10k_mbx_request_irq_pf (struct fm10k_intfc*) ; 
 int fm10k_mbx_request_irq_vf (struct fm10k_intfc*) ; 
 int stub1 (struct fm10k_hw*,TYPE_3__*) ; 

int fm10k_mbx_request_irq(struct fm10k_intfc *interface)
{
	struct fm10k_hw *hw = &interface->hw;
	int err;

	/* enable Mailbox cause */
	if (hw->mac.type == fm10k_mac_pf)
		err = fm10k_mbx_request_irq_pf(interface);
	else
		err = fm10k_mbx_request_irq_vf(interface);
	if (err)
		return err;

	/* connect mailbox */
	err = hw->mbx.ops.connect(hw, &hw->mbx);

	/* if the mailbox failed to connect, then free IRQ */
	if (err)
		fm10k_mbx_free_irq(interface);

	return err;
}