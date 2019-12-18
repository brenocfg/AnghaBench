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
struct palmas_gpadc {int /*<<< orphan*/  dev; int /*<<< orphan*/  palmas; } ;

/* Variables and functions */
 int /*<<< orphan*/  PALMAS_INT3_MASK ; 
 int /*<<< orphan*/  PALMAS_INT3_MASK_GPADC_EOC_SW ; 
 int /*<<< orphan*/  PALMAS_INTERRUPT_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int palmas_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int palmas_gpadc_start_mask_interrupt(struct palmas_gpadc *adc,
						bool mask)
{
	int ret;

	if (!mask)
		ret = palmas_update_bits(adc->palmas, PALMAS_INTERRUPT_BASE,
					PALMAS_INT3_MASK,
					PALMAS_INT3_MASK_GPADC_EOC_SW, 0);
	else
		ret = palmas_update_bits(adc->palmas, PALMAS_INTERRUPT_BASE,
					PALMAS_INT3_MASK,
					PALMAS_INT3_MASK_GPADC_EOC_SW,
					PALMAS_INT3_MASK_GPADC_EOC_SW);
	if (ret < 0)
		dev_err(adc->dev, "GPADC INT MASK update failed: %d\n", ret);

	return ret;
}