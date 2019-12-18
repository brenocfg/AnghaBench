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
struct fwnode_handle {int dummy; } ;
struct acpi_gpio_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 struct gpio_desc* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct gpio_desc *
acpi_node_get_gpiod(struct fwnode_handle *fwnode, const char *propname,
		    int index, struct acpi_gpio_info *info)
{
	return ERR_PTR(-ENXIO);
}