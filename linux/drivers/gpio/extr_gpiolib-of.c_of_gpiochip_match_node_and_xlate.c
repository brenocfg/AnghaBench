#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct of_phandle_args {scalar_t__ np; } ;
struct gpio_chip {scalar_t__ (* of_xlate ) (struct gpio_chip*,struct of_phandle_args*,int /*<<< orphan*/ *) ;TYPE_2__* gpiodev; } ;
struct TYPE_3__ {scalar_t__ of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct gpio_chip*,struct of_phandle_args*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int of_gpiochip_match_node_and_xlate(struct gpio_chip *chip, void *data)
{
	struct of_phandle_args *gpiospec = data;

	return chip->gpiodev->dev.of_node == gpiospec->np &&
				chip->of_xlate &&
				chip->of_xlate(chip, gpiospec, NULL) >= 0;
}