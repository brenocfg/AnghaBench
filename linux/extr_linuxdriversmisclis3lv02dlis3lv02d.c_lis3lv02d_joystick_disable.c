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
struct lis3lv02d {int /*<<< orphan*/ * idev; int /*<<< orphan*/  miscdev; scalar_t__ irq; TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ irq2; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct lis3lv02d*) ; 
 int /*<<< orphan*/  input_free_polled_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_polled_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

void lis3lv02d_joystick_disable(struct lis3lv02d *lis3)
{
	if (lis3->irq)
		free_irq(lis3->irq, lis3);
	if (lis3->pdata && lis3->pdata->irq2)
		free_irq(lis3->pdata->irq2, lis3);

	if (!lis3->idev)
		return;

	if (lis3->irq)
		misc_deregister(&lis3->miscdev);
	input_unregister_polled_device(lis3->idev);
	input_free_polled_device(lis3->idev);
	lis3->idev = NULL;
}