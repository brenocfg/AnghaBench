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
struct max8997_dev {scalar_t__ irq; scalar_t__ ono; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct max8997_dev*) ; 

void max8997_irq_exit(struct max8997_dev *max8997)
{
	if (max8997->ono)
		free_irq(max8997->ono, max8997);

	if (max8997->irq)
		free_irq(max8997->irq, max8997);
}