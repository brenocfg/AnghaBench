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
struct pcibus_info {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ sal_pcibr_error_interrupt (struct pcibus_info*) ; 

__attribute__((used)) static irqreturn_t
pcibr_error_intr_handler(int irq, void *arg)
{
	struct pcibus_info *soft = arg;

	if (sal_pcibr_error_interrupt(soft) < 0)
		panic("pcibr_error_intr_handler(): Fatal Bridge Error");

	return IRQ_HANDLED;
}