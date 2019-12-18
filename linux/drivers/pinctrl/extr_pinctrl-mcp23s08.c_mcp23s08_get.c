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
struct mcp23s08 {int cached_gpio; int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCP_GPIO ; 
 struct mcp23s08* gpiochip_get_data (struct gpio_chip*) ; 
 int mcp_read (struct mcp23s08*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcp23s08_get(struct gpio_chip *chip, unsigned offset)
{
	struct mcp23s08	*mcp = gpiochip_get_data(chip);
	int status, ret;

	mutex_lock(&mcp->lock);

	/* REVISIT reading this clears any IRQ ... */
	ret = mcp_read(mcp, MCP_GPIO, &status);
	if (ret < 0)
		status = 0;
	else {
		mcp->cached_gpio = status;
		status = !!(status & (1 << offset));
	}

	mutex_unlock(&mcp->lock);
	return status;
}