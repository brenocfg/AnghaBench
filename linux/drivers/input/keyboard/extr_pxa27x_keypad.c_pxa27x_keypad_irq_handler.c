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
struct pxa27x_keypad {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KPC ; 
 unsigned long KPC_DI ; 
 unsigned long KPC_MI ; 
 int /*<<< orphan*/  clear_wakeup_event (struct pxa27x_keypad*) ; 
 unsigned long keypad_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa27x_keypad_scan_direct (struct pxa27x_keypad*) ; 
 int /*<<< orphan*/  pxa27x_keypad_scan_matrix (struct pxa27x_keypad*) ; 

__attribute__((used)) static irqreturn_t pxa27x_keypad_irq_handler(int irq, void *dev_id)
{
	struct pxa27x_keypad *keypad = dev_id;
	unsigned long kpc = keypad_readl(KPC);

	clear_wakeup_event(keypad);

	if (kpc & KPC_DI)
		pxa27x_keypad_scan_direct(keypad);

	if (kpc & KPC_MI)
		pxa27x_keypad_scan_matrix(keypad);

	return IRQ_HANDLED;
}