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
 int ALX_ISR_DIS ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  alx_intr_handle (struct alx_priv*,int) ; 
 int alx_read_mem32 (struct alx_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t alx_intr_legacy(int irq, void *data)
{
	struct alx_priv *alx = data;
	struct alx_hw *hw = &alx->hw;
	u32 intr;

	intr = alx_read_mem32(hw, ALX_ISR);

	if (intr & ALX_ISR_DIS || !(intr & alx->int_mask))
		return IRQ_NONE;

	return alx_intr_handle(alx, intr);
}