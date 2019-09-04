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
struct pcf857x {int out; int (* write ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct pcf857x* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pcf857x_input(struct gpio_chip *chip, unsigned offset)
{
	struct pcf857x	*gpio = gpiochip_get_data(chip);
	int		status;

	mutex_lock(&gpio->lock);
	gpio->out |= (1 << offset);
	status = gpio->write(gpio->client, gpio->out);
	mutex_unlock(&gpio->lock);

	return status;
}