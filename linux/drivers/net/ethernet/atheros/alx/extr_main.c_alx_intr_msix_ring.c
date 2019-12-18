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
struct alx_napi {int /*<<< orphan*/  napi; int /*<<< orphan*/  vec_mask; int /*<<< orphan*/  vec_idx; TYPE_1__* alx; } ;
struct alx_hw {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct alx_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_ISR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  alx_mask_msix (struct alx_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t alx_intr_msix_ring(int irq, void *data)
{
	struct alx_napi *np = data;
	struct alx_hw *hw = &np->alx->hw;

	/* mask interrupt to ACK chip */
	alx_mask_msix(hw, np->vec_idx, true);
	/* clear interrupt status */
	alx_write_mem32(hw, ALX_ISR, np->vec_mask);

	napi_schedule(&np->napi);

	return IRQ_HANDLED;
}