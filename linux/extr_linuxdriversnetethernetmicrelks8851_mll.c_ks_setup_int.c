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
struct ks_net {int rc_ier; } ;

/* Variables and functions */
 int IRQ_LCI ; 
 int IRQ_RXI ; 
 int IRQ_TXI ; 
 int /*<<< orphan*/  KS_ISR ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ks_setup_int(struct ks_net *ks)
{
	ks->rc_ier = 0x00;
	/* Clear the interrupts status of the hardware. */
	ks_wrreg16(ks, KS_ISR, 0xffff);

	/* Enables the interrupts of the hardware. */
	ks->rc_ier = (IRQ_LCI | IRQ_TXI | IRQ_RXI);
}