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
 int /*<<< orphan*/  IMX_GPIO_NR (int,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mx27ads_sdhc2_exit(struct device *dev, void *data)
{
	free_irq(gpio_to_irq(IMX_GPIO_NR(2, 7)), data);
}