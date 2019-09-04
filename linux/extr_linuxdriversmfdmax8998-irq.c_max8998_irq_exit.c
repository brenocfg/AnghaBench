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
struct max8998_dev {scalar_t__ irq; scalar_t__ ono; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct max8998_dev*) ; 

void max8998_irq_exit(struct max8998_dev *max8998)
{
	if (max8998->ono)
		free_irq(max8998->ono, max8998);

	if (max8998->irq)
		free_irq(max8998->irq, max8998);
}