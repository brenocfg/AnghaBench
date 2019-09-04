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
struct irte {int present; int vector; int redir_hint; int /*<<< orphan*/  dest_id; int /*<<< orphan*/  dlvry_mode; scalar_t__ trigger_mode; int /*<<< orphan*/  dst_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_delivery_mode; int /*<<< orphan*/  irq_dest_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRTE_DEST (unsigned int) ; 
 TYPE_1__* apic ; 
 int /*<<< orphan*/  memset (struct irte*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void prepare_irte(struct irte *irte, int vector, unsigned int dest)
{
	memset(irte, 0, sizeof(*irte));

	irte->present = 1;
	irte->dst_mode = apic->irq_dest_mode;
	/*
	 * Trigger mode in the IRTE will always be edge, and for IO-APIC, the
	 * actual level or edge trigger will be setup in the IO-APIC
	 * RTE. This will help simplify level triggered irq migration.
	 * For more details, see the comments (in io_apic.c) explainig IO-APIC
	 * irq migration in the presence of interrupt-remapping.
	*/
	irte->trigger_mode = 0;
	irte->dlvry_mode = apic->irq_delivery_mode;
	irte->vector = vector;
	irte->dest_id = IRTE_DEST(dest);
	irte->redir_hint = 1;
}