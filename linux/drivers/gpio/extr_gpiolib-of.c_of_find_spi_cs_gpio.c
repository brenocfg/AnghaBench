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
struct gpio_desc {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SPI_MASTER ; 
 int /*<<< orphan*/  ENOENT ; 
 struct gpio_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 struct gpio_desc* of_find_gpio (struct device*,int /*<<< orphan*/ *,unsigned int,unsigned long*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static struct gpio_desc *of_find_spi_cs_gpio(struct device *dev,
					     const char *con_id,
					     unsigned int idx,
					     unsigned long *flags)
{
	struct device_node *np = dev->of_node;

	if (!IS_ENABLED(CONFIG_SPI_MASTER))
		return ERR_PTR(-ENOENT);

	/* Allow this specifically for Freescale devices */
	if (!of_device_is_compatible(np, "fsl,spi") &&
	    !of_device_is_compatible(np, "aeroflexgaisler,spictrl"))
		return ERR_PTR(-ENOENT);
	/* Allow only if asking for "cs-gpios" */
	if (!con_id || strcmp(con_id, "cs"))
		return ERR_PTR(-ENOENT);

	/*
	 * While all other SPI controllers use "cs-gpios" the Freescale
	 * uses just "gpios" so translate to that when "cs-gpios" is
	 * requested.
	 */
	return of_find_gpio(dev, NULL, idx, flags);
}