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
struct lm3533 {int /*<<< orphan*/  gpio_hwen; } ;

/* Variables and functions */
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lm3533_disable(struct lm3533 *lm3533)
{
	if (gpio_is_valid(lm3533->gpio_hwen))
		gpio_set_value(lm3533->gpio_hwen, 0);
}