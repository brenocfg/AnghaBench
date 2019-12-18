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
typedef  int /*<<< orphan*/  u32 ;
struct alx_priv {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_ISR ; 
 scalar_t__ ALX_ISR_DIS ; 
 int /*<<< orphan*/  alx_configure (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_irq_enable (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_reinit_rings (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_schedule_link_check (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_write_mem32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alx_activate(struct alx_priv *alx)
{
	/* hardware setting lost, restore it */
	alx_reinit_rings(alx);
	alx_configure(alx);

	/* clear old interrupts */
	alx_write_mem32(&alx->hw, ALX_ISR, ~(u32)ALX_ISR_DIS);

	alx_irq_enable(alx);

	alx_schedule_link_check(alx);
}