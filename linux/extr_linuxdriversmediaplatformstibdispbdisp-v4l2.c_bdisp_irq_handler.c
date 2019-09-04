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
struct bdisp_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 scalar_t__ bdisp_hw_get_and_clear_irq (struct bdisp_dev*) ; 

__attribute__((used)) static irqreturn_t bdisp_irq_handler(int irq, void *priv)
{
	if (bdisp_hw_get_and_clear_irq((struct bdisp_dev *)priv))
		return IRQ_NONE;
	else
		return IRQ_WAKE_THREAD;
}