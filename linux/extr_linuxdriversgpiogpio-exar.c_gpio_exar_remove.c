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
struct platform_device {int dummy; } ;
struct exar_gpio_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_index ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct exar_gpio_chip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int gpio_exar_remove(struct platform_device *pdev)
{
	struct exar_gpio_chip *exar_gpio = platform_get_drvdata(pdev);

	ida_simple_remove(&ida_index, exar_gpio->index);
	mutex_destroy(&exar_gpio->lock);

	return 0;
}