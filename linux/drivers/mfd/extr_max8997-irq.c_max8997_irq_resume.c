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
struct max8997_dev {scalar_t__ irq_domain; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  max8997_irq_thread (int /*<<< orphan*/ ,struct max8997_dev*) ; 

int max8997_irq_resume(struct max8997_dev *max8997)
{
	if (max8997->irq && max8997->irq_domain)
		max8997_irq_thread(0, max8997);
	return 0;
}