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
typedef  int /*<<< orphan*/  u32 ;
struct max6697_platform_data {int resistance_cancellation; void* ideality_value; void* ideality_mask; void* over_temperature_mask; void* alert_mask; void* beta_compensation; void* extended_range_enable; void* smbus_timeout_disable; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static void max6697_get_config_of(struct device_node *node,
				  struct max6697_platform_data *pdata)
{
	int len;
	const __be32 *prop;

	pdata->smbus_timeout_disable =
		of_property_read_bool(node, "smbus-timeout-disable");
	pdata->extended_range_enable =
		of_property_read_bool(node, "extended-range-enable");
	pdata->beta_compensation =
		of_property_read_bool(node, "beta-compensation-enable");

	prop = of_get_property(node, "alert-mask", &len);
	if (prop && len == sizeof(u32))
		pdata->alert_mask = be32_to_cpu(prop[0]);
	prop = of_get_property(node, "over-temperature-mask", &len);
	if (prop && len == sizeof(u32))
		pdata->over_temperature_mask = be32_to_cpu(prop[0]);
	prop = of_get_property(node, "resistance-cancellation", &len);
	if (prop) {
		if (len == sizeof(u32))
			pdata->resistance_cancellation = be32_to_cpu(prop[0]);
		else
			pdata->resistance_cancellation = 0xfe;
	}
	prop = of_get_property(node, "transistor-ideality", &len);
	if (prop && len == 2 * sizeof(u32)) {
			pdata->ideality_mask = be32_to_cpu(prop[0]);
			pdata->ideality_value = be32_to_cpu(prop[1]);
	}
}