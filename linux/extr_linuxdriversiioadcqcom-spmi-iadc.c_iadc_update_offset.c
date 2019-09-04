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
struct iadc_chip {scalar_t__ gain; scalar_t__* offset; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IADC_EXT_OFFSET_CSP_CSN ; 
 size_t IADC_EXT_RSENSE ; 
 int /*<<< orphan*/  IADC_GAIN_17P857MV ; 
 int /*<<< orphan*/  IADC_INT_OFFSET_CSP2_CSN2 ; 
 size_t IADC_INT_RSENSE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int iadc_do_conversion (struct iadc_chip*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int iadc_update_offset(struct iadc_chip *iadc)
{
	int ret;

	ret = iadc_do_conversion(iadc, IADC_GAIN_17P857MV, &iadc->gain);
	if (ret < 0)
		return ret;

	ret = iadc_do_conversion(iadc, IADC_INT_OFFSET_CSP2_CSN2,
				 &iadc->offset[IADC_INT_RSENSE]);
	if (ret < 0)
		return ret;

	if (iadc->gain == iadc->offset[IADC_INT_RSENSE]) {
		dev_err(iadc->dev, "error: internal offset == gain %d\n",
			iadc->gain);
		return -EINVAL;
	}

	ret = iadc_do_conversion(iadc, IADC_EXT_OFFSET_CSP_CSN,
				 &iadc->offset[IADC_EXT_RSENSE]);
	if (ret < 0)
		return ret;

	if (iadc->gain == iadc->offset[IADC_EXT_RSENSE]) {
		dev_err(iadc->dev, "error: external offset == gain %d\n",
			iadc->gain);
		return -EINVAL;
	}

	return 0;
}