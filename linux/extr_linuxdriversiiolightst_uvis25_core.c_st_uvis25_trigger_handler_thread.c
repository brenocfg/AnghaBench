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
struct st_uvis25_hw {int /*<<< orphan*/  trig; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ST_UVIS25_REG_STATUS_ADDR ; 
 int ST_UVIS25_REG_UV_DA_MASK ; 
 int /*<<< orphan*/  iio_trigger_poll_chained (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static irqreturn_t st_uvis25_trigger_handler_thread(int irq, void *private)
{
	struct st_uvis25_hw *hw = private;
	int err, status;

	err = regmap_read(hw->regmap, ST_UVIS25_REG_STATUS_ADDR, &status);
	if (err < 0)
		return IRQ_HANDLED;

	if (!(status & ST_UVIS25_REG_UV_DA_MASK))
		return IRQ_NONE;

	iio_trigger_poll_chained(hw->trig);

	return IRQ_HANDLED;
}