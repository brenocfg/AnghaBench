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
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX23417_RESET ; 
 int /*<<< orphan*/  cx231xx_set_gpio_value (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void cx231xx_reset_out(struct cx231xx *dev)
{
	cx231xx_set_gpio_value(dev, CX23417_RESET, 1);
	msleep(200);
	cx231xx_set_gpio_value(dev, CX23417_RESET, 0);
	msleep(200);
	cx231xx_set_gpio_value(dev, CX23417_RESET, 1);
}