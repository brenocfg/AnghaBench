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
typedef  int /*<<< orphan*/  u16 ;
struct gpio_desc {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct gpio_desc* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  chip_err (struct gpio_chip*,char*) ; 
 struct gpio_desc* gpiochip_get_desc (struct gpio_chip*,int /*<<< orphan*/ ) ; 
 int gpiod_request_commit (struct gpio_desc*,char const*) ; 

struct gpio_desc *gpiochip_request_own_desc(struct gpio_chip *chip, u16 hwnum,
					    const char *label)
{
	struct gpio_desc *desc = gpiochip_get_desc(chip, hwnum);
	int err;

	if (IS_ERR(desc)) {
		chip_err(chip, "failed to get GPIO descriptor\n");
		return desc;
	}

	err = gpiod_request_commit(desc, label);
	if (err < 0)
		return ERR_PTR(err);

	return desc;
}