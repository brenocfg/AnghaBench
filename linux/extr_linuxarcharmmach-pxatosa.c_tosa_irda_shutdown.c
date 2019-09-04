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
struct device {int dummy; } ;

/* Variables and functions */
 int IR_OFF ; 
 int IR_SIRMODE ; 
 int /*<<< orphan*/  TOSA_GPIO_IRDA_TX ; 
 int /*<<< orphan*/  TOSA_GPIO_IR_POWERDWN ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tosa_irda_transceiver_mode (struct device*,int) ; 

__attribute__((used)) static void tosa_irda_shutdown(struct device *dev)
{
	tosa_irda_transceiver_mode(dev, IR_SIRMODE | IR_OFF);
	gpio_free(TOSA_GPIO_IR_POWERDWN);
	gpio_free(TOSA_GPIO_IRDA_TX);
}