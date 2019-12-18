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
typedef  scalar_t__ u8 ;
struct iadc_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IADC_PERPH_SUBTYPE ; 
 scalar_t__ IADC_PERPH_SUBTYPE_IADC ; 
 int /*<<< orphan*/  IADC_PERPH_TYPE ; 
 scalar_t__ IADC_PERPH_TYPE_ADC ; 
 int /*<<< orphan*/  IADC_REVISION2 ; 
 scalar_t__ IADC_REVISION2_SUPPORTED_IADC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int iadc_read (struct iadc_chip*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int iadc_version_check(struct iadc_chip *iadc)
{
	u8 val;
	int ret;

	ret = iadc_read(iadc, IADC_PERPH_TYPE, &val);
	if (ret < 0)
		return ret;

	if (val < IADC_PERPH_TYPE_ADC) {
		dev_err(iadc->dev, "%d is not ADC\n", val);
		return -EINVAL;
	}

	ret = iadc_read(iadc, IADC_PERPH_SUBTYPE, &val);
	if (ret < 0)
		return ret;

	if (val < IADC_PERPH_SUBTYPE_IADC) {
		dev_err(iadc->dev, "%d is not IADC\n", val);
		return -EINVAL;
	}

	ret = iadc_read(iadc, IADC_REVISION2, &val);
	if (ret < 0)
		return ret;

	if (val < IADC_REVISION2_SUPPORTED_IADC) {
		dev_err(iadc->dev, "revision %d not supported\n", val);
		return -EINVAL;
	}

	return 0;
}