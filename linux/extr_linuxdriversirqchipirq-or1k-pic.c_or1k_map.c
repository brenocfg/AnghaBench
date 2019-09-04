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
struct or1k_pic_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  handle; int /*<<< orphan*/  chip; } ;
struct irq_domain {struct or1k_pic_dev* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int or1k_map(struct irq_domain *d, unsigned int irq, irq_hw_number_t hw)
{
	struct or1k_pic_dev *pic = d->host_data;

	irq_set_chip_and_handler(irq, &pic->chip, pic->handle);
	irq_set_status_flags(irq, pic->flags);

	return 0;
}