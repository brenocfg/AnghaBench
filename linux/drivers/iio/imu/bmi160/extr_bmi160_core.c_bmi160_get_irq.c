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
struct device_node {int dummy; } ;
typedef  enum bmi160_int_pin { ____Placeholder_bmi160_int_pin } bmi160_int_pin ;

/* Variables and functions */
 int BMI160_PIN_INT1 ; 
 int BMI160_PIN_INT2 ; 
 int of_irq_get_byname (struct device_node*,char*) ; 

__attribute__((used)) static int bmi160_get_irq(struct device_node *of_node, enum bmi160_int_pin *pin)
{
	int irq;

	/* Use INT1 if possible, otherwise fall back to INT2. */
	irq = of_irq_get_byname(of_node, "INT1");
	if (irq > 0) {
		*pin = BMI160_PIN_INT1;
		return irq;
	}

	irq = of_irq_get_byname(of_node, "INT2");
	if (irq > 0)
		*pin = BMI160_PIN_INT2;

	return irq;
}