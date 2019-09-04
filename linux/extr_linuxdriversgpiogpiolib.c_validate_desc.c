#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpio_desc {TYPE_1__* gdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct gpio_desc const*) ; 
 int PTR_ERR (struct gpio_desc const*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 

__attribute__((used)) static int validate_desc(const struct gpio_desc *desc, const char *func)
{
	if (!desc)
		return 0;
	if (IS_ERR(desc)) {
		pr_warn("%s: invalid GPIO (errorpointer)\n", func);
		return PTR_ERR(desc);
	}
	if (!desc->gdev) {
		pr_warn("%s: invalid GPIO (no device)\n", func);
		return -EINVAL;
	}
	if (!desc->gdev->chip) {
		dev_warn(&desc->gdev->dev,
			 "%s: backing chip is gone\n", func);
		return 0;
	}
	return 1;
}