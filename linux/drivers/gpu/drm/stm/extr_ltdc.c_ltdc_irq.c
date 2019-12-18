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
struct ltdc_device {int /*<<< orphan*/  irq_status; int /*<<< orphan*/  regs; } ;
struct drm_device {struct ltdc_device* dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  LTDC_ICR ; 
 int /*<<< orphan*/  LTDC_ISR ; 
 int /*<<< orphan*/  reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ltdc_irq(int irq, void *arg)
{
	struct drm_device *ddev = arg;
	struct ltdc_device *ldev = ddev->dev_private;

	/* Read & Clear the interrupt status */
	ldev->irq_status = reg_read(ldev->regs, LTDC_ISR);
	reg_write(ldev->regs, LTDC_ICR, ldev->irq_status);

	return IRQ_WAKE_THREAD;
}