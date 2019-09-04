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
struct hts221_hw {int /*<<< orphan*/  trig; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTS221_REG_STATUS_ADDR ; 
 int HTS221_RH_DRDY_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  iio_trigger_poll_chained (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static irqreturn_t hts221_trigger_handler_thread(int irq, void *private)
{
	struct hts221_hw *hw = private;
	int err, status;

	err = regmap_read(hw->regmap, HTS221_REG_STATUS_ADDR, &status);
	if (err < 0)
		return IRQ_HANDLED;

	/*
	 * H_DA bit (humidity data available) is routed to DRDY line.
	 * Humidity sample is computed after temperature one.
	 * Here we can assume data channels are both available if H_DA bit
	 * is set in status register
	 */
	if (!(status & HTS221_RH_DRDY_MASK))
		return IRQ_NONE;

	iio_trigger_poll_chained(hw->trig);

	return IRQ_HANDLED;
}