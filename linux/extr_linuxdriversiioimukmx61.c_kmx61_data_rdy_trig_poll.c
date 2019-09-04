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
struct kmx61_data {scalar_t__ ev_enable_state; int /*<<< orphan*/  motion_trig; scalar_t__ motion_trig_on; int /*<<< orphan*/  mag_dready_trig; scalar_t__ mag_dready_trig_on; int /*<<< orphan*/  acc_dready_trig; scalar_t__ acc_dready_trig_on; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  iio_trigger_poll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t kmx61_data_rdy_trig_poll(int irq, void *private)
{
	struct kmx61_data *data = private;

	if (data->acc_dready_trig_on)
		iio_trigger_poll(data->acc_dready_trig);
	if (data->mag_dready_trig_on)
		iio_trigger_poll(data->mag_dready_trig);

	if (data->motion_trig_on)
		iio_trigger_poll(data->motion_trig);

	if (data->ev_enable_state)
		return IRQ_WAKE_THREAD;
	return IRQ_HANDLED;
}