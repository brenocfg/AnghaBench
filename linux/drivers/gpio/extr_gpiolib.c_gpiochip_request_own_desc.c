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
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;
typedef  enum gpio_lookup_flags { ____Placeholder_gpio_lookup_flags } gpio_lookup_flags ;

/* Variables and functions */
 struct gpio_desc* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  chip_err (struct gpio_chip*,char*,...) ; 
 struct gpio_desc* gpiochip_get_desc (struct gpio_chip*,int /*<<< orphan*/ ) ; 
 int gpiod_configure_flags (struct gpio_desc*,char const*,int,int) ; 
 int /*<<< orphan*/  gpiod_free_commit (struct gpio_desc*) ; 
 int gpiod_request_commit (struct gpio_desc*,char const*) ; 

struct gpio_desc *gpiochip_request_own_desc(struct gpio_chip *chip, u16 hwnum,
					    const char *label,
					    enum gpio_lookup_flags lflags,
					    enum gpiod_flags dflags)
{
	struct gpio_desc *desc = gpiochip_get_desc(chip, hwnum);
	int ret;

	if (IS_ERR(desc)) {
		chip_err(chip, "failed to get GPIO descriptor\n");
		return desc;
	}

	ret = gpiod_request_commit(desc, label);
	if (ret < 0)
		return ERR_PTR(ret);

	ret = gpiod_configure_flags(desc, label, lflags, dflags);
	if (ret) {
		chip_err(chip, "setup of own GPIO %s failed\n", label);
		gpiod_free_commit(desc);
		return ERR_PTR(ret);
	}

	return desc;
}