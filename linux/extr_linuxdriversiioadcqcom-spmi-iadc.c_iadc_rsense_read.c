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
typedef  int u8 ;
struct iadc_chip {int* rsense; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t IADC_EXT_RSENSE ; 
 size_t IADC_INT_RSENSE ; 
 int IADC_INT_RSENSE_DEVIATION ; 
 int IADC_INT_RSENSE_IDEAL_VALUE ; 
 int /*<<< orphan*/  IADC_NOMINAL_RSENSE ; 
 int IADC_NOMINAL_RSENSE_SIGN_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int iadc_read (struct iadc_chip*,int /*<<< orphan*/ ,int*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int iadc_rsense_read(struct iadc_chip *iadc, struct device_node *node)
{
	int ret, sign, int_sense;
	u8 deviation;

	ret = of_property_read_u32(node, "qcom,external-resistor-micro-ohms",
				   &iadc->rsense[IADC_EXT_RSENSE]);
	if (ret < 0)
		iadc->rsense[IADC_EXT_RSENSE] = IADC_INT_RSENSE_IDEAL_VALUE;

	if (!iadc->rsense[IADC_EXT_RSENSE]) {
		dev_err(iadc->dev, "external resistor can't be zero Ohms");
		return -EINVAL;
	}

	ret = iadc_read(iadc, IADC_NOMINAL_RSENSE, &deviation);
	if (ret < 0)
		return ret;

	/*
	 * Deviation value stored is an offset from 10 mili Ohms, bit 7 is
	 * the sign, the remaining bits have an LSB of 15625 nano Ohms.
	 */
	sign = (deviation & IADC_NOMINAL_RSENSE_SIGN_MASK) ? -1 : 1;

	deviation &= ~IADC_NOMINAL_RSENSE_SIGN_MASK;

	/* Scale it to nono Ohms */
	int_sense = IADC_INT_RSENSE_IDEAL_VALUE * 1000;
	int_sense += sign * deviation * IADC_INT_RSENSE_DEVIATION;
	int_sense /= 1000; /* micro Ohms */

	iadc->rsense[IADC_INT_RSENSE] = int_sense;
	return 0;
}