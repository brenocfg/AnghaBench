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
struct irq_desc {int dummy; } ;
struct TYPE_2__ {unsigned short intreqr; unsigned short intenar; unsigned short intreq; } ;

/* Variables and functions */
 unsigned short IF_AUD0 ; 
 unsigned short IF_AUD1 ; 
 unsigned short IF_AUD2 ; 
 unsigned short IF_AUD3 ; 
 int /*<<< orphan*/  IRQ_AMIGA_AUD0 ; 
 int /*<<< orphan*/  IRQ_AMIGA_AUD1 ; 
 int /*<<< orphan*/  IRQ_AMIGA_AUD2 ; 
 int /*<<< orphan*/  IRQ_AMIGA_AUD3 ; 
 TYPE_1__ amiga_custom ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ami_int4(struct irq_desc *desc)
{
	unsigned short ints = amiga_custom.intreqr & amiga_custom.intenar;

	/* if audio 0 interrupt */
	if (ints & IF_AUD0) {
		amiga_custom.intreq = IF_AUD0;
		generic_handle_irq(IRQ_AMIGA_AUD0);
	}

	/* if audio 1 interrupt */
	if (ints & IF_AUD1) {
		amiga_custom.intreq = IF_AUD1;
		generic_handle_irq(IRQ_AMIGA_AUD1);
	}

	/* if audio 2 interrupt */
	if (ints & IF_AUD2) {
		amiga_custom.intreq = IF_AUD2;
		generic_handle_irq(IRQ_AMIGA_AUD2);
	}

	/* if audio 3 interrupt */
	if (ints & IF_AUD3) {
		amiga_custom.intreq = IF_AUD3;
		generic_handle_irq(IRQ_AMIGA_AUD3);
	}
}