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
struct wm8994 {int dummy; } ;
struct irq_domain {struct wm8994* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct wm8994*) ; 
 int /*<<< orphan*/  irq_set_nested_thread (unsigned int,int) ; 
 int /*<<< orphan*/  irq_set_noprobe (unsigned int) ; 
 int /*<<< orphan*/  wm8994_edge_irq_chip ; 

__attribute__((used)) static int wm8994_edge_irq_map(struct irq_domain *h, unsigned int virq,
			       irq_hw_number_t hw)
{
	struct wm8994 *wm8994 = h->host_data;

	irq_set_chip_data(virq, wm8994);
	irq_set_chip_and_handler(virq, &wm8994_edge_irq_chip, handle_edge_irq);
	irq_set_nested_thread(virq, 1);
	irq_set_noprobe(virq);

	return 0;
}