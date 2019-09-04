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
struct ad_sigma_delta {int irq_dis; int /*<<< orphan*/  trig; int /*<<< orphan*/  completion; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  iio_trigger_poll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ad_sd_data_rdy_trig_poll(int irq, void *private)
{
	struct ad_sigma_delta *sigma_delta = private;

	complete(&sigma_delta->completion);
	disable_irq_nosync(irq);
	sigma_delta->irq_dis = true;
	iio_trigger_poll(sigma_delta->trig);

	return IRQ_HANDLED;
}