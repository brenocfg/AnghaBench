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
struct spa {int /*<<< orphan*/  irq_name; scalar_t__ virq; } ;
struct ocxl_link {struct spa* spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct ocxl_link*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_irq_registers (struct spa*) ; 

__attribute__((used)) static void release_xsl_irq(struct ocxl_link *link)
{
	struct spa *spa = link->spa;

	if (spa->virq) {
		free_irq(spa->virq, link);
		irq_dispose_mapping(spa->virq);
	}
	kfree(spa->irq_name);
	unmap_irq_registers(spa);
}