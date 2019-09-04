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
struct lp55xx_led {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct lp55xx_led* cdev_to_lp55xx_led (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct lp55xx_led *dev_to_lp55xx_led(struct device *dev)
{
	return cdev_to_lp55xx_led(dev_get_drvdata(dev));
}