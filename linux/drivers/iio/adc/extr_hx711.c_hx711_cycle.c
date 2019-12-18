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
struct hx711_data {int /*<<< orphan*/  gpiod_dout; int /*<<< orphan*/  data_ready_delay_ns; int /*<<< orphan*/  gpiod_pd_sck; } ;

/* Variables and functions */
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hx711_cycle(struct hx711_data *hx711_data)
{
	unsigned long flags;

	/*
	 * if preempted for more then 60us while PD_SCK is high:
	 * hx711 is going in reset
	 * ==> measuring is false
	 */
	local_irq_save(flags);
	gpiod_set_value(hx711_data->gpiod_pd_sck, 1);

	/*
	 * wait until DOUT is ready
	 * it turned out that parasitic capacities are extending the time
	 * until DOUT has reached it's value
	 */
	ndelay(hx711_data->data_ready_delay_ns);

	/*
	 * here we are not waiting for 0.2 us as suggested by the datasheet,
	 * because the oscilloscope showed in a test scenario
	 * at least 1.15 us for PD_SCK high (T3 in datasheet)
	 * and 0.56 us for PD_SCK low on TI Sitara with 800 MHz
	 */
	gpiod_set_value(hx711_data->gpiod_pd_sck, 0);
	local_irq_restore(flags);

	/*
	 * make it a square wave for addressing cases with capacitance on
	 * PC_SCK
	 */
	ndelay(hx711_data->data_ready_delay_ns);

	/* sample as late as possible */
	return gpiod_get_value(hx711_data->gpiod_dout);
}