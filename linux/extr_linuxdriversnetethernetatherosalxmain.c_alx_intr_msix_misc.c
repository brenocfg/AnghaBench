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
typedef  int u32 ;
struct alx_hw {int dummy; } ;
struct alx_priv {int int_mask; struct alx_hw hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_ISR ; 
 int ALX_ISR_ALL_QUEUES ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ alx_intr_handle_misc (struct alx_priv*,int) ; 
 int /*<<< orphan*/  alx_mask_msix (struct alx_hw*,int /*<<< orphan*/ ,int) ; 
 int alx_read_mem32 (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t alx_intr_msix_misc(int irq, void *data)
{
	struct alx_priv *alx = data;
	struct alx_hw *hw = &alx->hw;
	u32 intr;

	/* mask interrupt to ACK chip */
	alx_mask_msix(hw, 0, true);

	/* read interrupt status */
	intr = alx_read_mem32(hw, ALX_ISR);
	intr &= (alx->int_mask & ~ALX_ISR_ALL_QUEUES);

	if (alx_intr_handle_misc(alx, intr))
		return IRQ_HANDLED;

	/* clear interrupt status */
	alx_write_mem32(hw, ALX_ISR, intr);

	/* enable interrupt again */
	alx_mask_msix(hw, 0, false);

	return IRQ_HANDLED;
}