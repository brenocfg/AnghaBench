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
struct sun4i_lradc_data {int /*<<< orphan*/  vref_supply; scalar_t__ base; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int FIRST_CONVERT_DLY (int) ; 
 int HOLD_EN (int) ; 
 int LEVELA_B_CNT (int) ; 
 scalar_t__ LRADC_CTRL ; 
 scalar_t__ LRADC_INTC ; 
 int SAMPLE_RATE (int) ; 
 struct sun4i_lradc_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sun4i_lradc_close(struct input_dev *dev)
{
	struct sun4i_lradc_data *lradc = input_get_drvdata(dev);

	/* Disable lradc, leave other settings unchanged */
	writel(FIRST_CONVERT_DLY(2) | LEVELA_B_CNT(1) | HOLD_EN(1) |
		SAMPLE_RATE(2), lradc->base + LRADC_CTRL);
	writel(0, lradc->base + LRADC_INTC);

	regulator_disable(lradc->vref_supply);
}