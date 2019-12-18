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
struct sun4i_lradc_data {int vref; scalar_t__ base; TYPE_1__* variant; int /*<<< orphan*/  vref_supply; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int divisor_numerator; int divisor_denominator; } ;

/* Variables and functions */
 int CHAN0_KEYDOWN_IRQ ; 
 int CHAN0_KEYUP_IRQ ; 
 int ENABLE (int) ; 
 int FIRST_CONVERT_DLY (int) ; 
 int HOLD_EN (int) ; 
 int LEVELA_B_CNT (int) ; 
 scalar_t__ LRADC_CTRL ; 
 scalar_t__ LRADC_INTC ; 
 int SAMPLE_RATE (int /*<<< orphan*/ ) ; 
 struct sun4i_lradc_data* input_get_drvdata (struct input_dev*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sun4i_lradc_open(struct input_dev *dev)
{
	struct sun4i_lradc_data *lradc = input_get_drvdata(dev);
	int error;

	error = regulator_enable(lradc->vref_supply);
	if (error)
		return error;

	lradc->vref = regulator_get_voltage(lradc->vref_supply) *
		      lradc->variant->divisor_numerator /
		      lradc->variant->divisor_denominator;
	/*
	 * Set sample time to 4 ms / 250 Hz. Wait 2 * 4 ms for key to
	 * stabilize on press, wait (1 + 1) * 4 ms for key release
	 */
	writel(FIRST_CONVERT_DLY(2) | LEVELA_B_CNT(1) | HOLD_EN(1) |
		SAMPLE_RATE(0) | ENABLE(1), lradc->base + LRADC_CTRL);

	writel(CHAN0_KEYUP_IRQ | CHAN0_KEYDOWN_IRQ, lradc->base + LRADC_INTC);

	return 0;
}