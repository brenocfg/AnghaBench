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
struct ssp_data {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ssp_irq_msg (struct ssp_data*) ; 

__attribute__((used)) static irqreturn_t ssp_irq_thread_fn(int irq, void *dev_id)
{
	struct ssp_data *data = dev_id;

	/*
	 * This wrapper is done to preserve error path for ssp_irq_msg, also
	 * it is defined in different file.
	 */
	ssp_irq_msg(data);

	return IRQ_HANDLED;
}