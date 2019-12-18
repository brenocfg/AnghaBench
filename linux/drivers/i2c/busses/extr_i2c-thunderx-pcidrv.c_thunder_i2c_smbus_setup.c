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
struct octeon_i2c {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  acpi_disabled ; 
 int thunder_i2c_smbus_setup_of (struct octeon_i2c*,struct device_node*) ; 

__attribute__((used)) static int thunder_i2c_smbus_setup(struct octeon_i2c *i2c,
				   struct device_node *node)
{
	/* TODO: ACPI support */
	if (!acpi_disabled)
		return -EOPNOTSUPP;

	return thunder_i2c_smbus_setup_of(i2c, node);
}