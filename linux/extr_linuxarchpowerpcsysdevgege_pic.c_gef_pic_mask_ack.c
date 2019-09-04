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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gef_pic_mask (struct irq_data*) ; 

__attribute__((used)) static void gef_pic_mask_ack(struct irq_data *d)
{
	/* Don't think we actually have to do anything to ack an interrupt,
	 * we just need to clear down the devices interrupt and it will go away
	 */
	gef_pic_mask(d);
}