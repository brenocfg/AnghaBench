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
struct pmic_gpio_state {int /*<<< orphan*/  dev; int /*<<< orphan*/  map; } ;
struct pmic_gpio_pad {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

__attribute__((used)) static int pmic_gpio_read(struct pmic_gpio_state *state,
			  struct pmic_gpio_pad *pad, unsigned int addr)
{
	unsigned int val;
	int ret;

	ret = regmap_read(state->map, pad->base + addr, &val);
	if (ret < 0)
		dev_err(state->dev, "read 0x%x failed\n", addr);
	else
		ret = val;

	return ret;
}