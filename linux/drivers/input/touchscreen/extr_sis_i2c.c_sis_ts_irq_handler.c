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
struct sis_ts_data {scalar_t__ attn_gpio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ gpiod_get_value_cansleep (scalar_t__) ; 
 int /*<<< orphan*/  sis_ts_handle_packet (struct sis_ts_data*) ; 

__attribute__((used)) static irqreturn_t sis_ts_irq_handler(int irq, void *dev_id)
{
	struct sis_ts_data *ts = dev_id;

	do {
		sis_ts_handle_packet(ts);
	} while (ts->attn_gpio && gpiod_get_value_cansleep(ts->attn_gpio));

	return IRQ_HANDLED;
}