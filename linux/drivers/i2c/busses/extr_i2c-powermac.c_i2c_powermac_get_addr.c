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
typedef  int u32 ;
struct pmac_i2c_bus {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 scalar_t__ of_node_name_eq (struct device_node*,char*) ; 

__attribute__((used)) static u32 i2c_powermac_get_addr(struct i2c_adapter *adap,
					   struct pmac_i2c_bus *bus,
					   struct device_node *node)
{
	const __be32 *prop;
	int len;

	/* First check for valid "reg" */
	prop = of_get_property(node, "reg", &len);
	if (prop && (len >= sizeof(int)))
		return (be32_to_cpup(prop) & 0xff) >> 1;

	/* Then check old-style "i2c-address" */
	prop = of_get_property(node, "i2c-address", &len);
	if (prop && (len >= sizeof(int)))
		return (be32_to_cpup(prop) & 0xff) >> 1;

	/* Now handle some devices with missing "reg" properties */
	if (of_node_name_eq(node, "cereal"))
		return 0x60;
	else if (of_node_name_eq(node, "deq"))
		return 0x34;

	dev_warn(&adap->dev, "No i2c address for %pOF\n", node);

	return 0xffffffff;
}