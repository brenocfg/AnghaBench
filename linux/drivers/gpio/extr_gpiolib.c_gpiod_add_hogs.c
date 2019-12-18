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
struct gpiod_hog {scalar_t__ chip_label; int /*<<< orphan*/  list; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct gpio_chip* find_chip_by_name (scalar_t__) ; 
 int /*<<< orphan*/  gpio_machine_hogs ; 
 int /*<<< orphan*/  gpio_machine_hogs_mutex ; 
 int /*<<< orphan*/  gpiochip_machine_hog (struct gpio_chip*,struct gpiod_hog*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void gpiod_add_hogs(struct gpiod_hog *hogs)
{
	struct gpio_chip *chip;
	struct gpiod_hog *hog;

	mutex_lock(&gpio_machine_hogs_mutex);

	for (hog = &hogs[0]; hog->chip_label; hog++) {
		list_add_tail(&hog->list, &gpio_machine_hogs);

		/*
		 * The chip may have been registered earlier, so check if it
		 * exists and, if so, try to hog the line now.
		 */
		chip = find_chip_by_name(hog->chip_label);
		if (chip)
			gpiochip_machine_hog(chip, hog);
	}

	mutex_unlock(&gpio_machine_hogs_mutex);
}