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
struct max8998_dev {scalar_t__ irq; scalar_t__ irq_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  max8998_irq_thread (scalar_t__,struct max8998_dev*) ; 

int max8998_irq_resume(struct max8998_dev *max8998)
{
	if (max8998->irq && max8998->irq_domain)
		max8998_irq_thread(max8998->irq, max8998);
	return 0;
}