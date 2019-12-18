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
typedef  size_t u32 ;
struct ina3221_input {int disconnected; size_t shunt_resistor; int /*<<< orphan*/  label; } ;
struct ina3221_data {struct ina3221_input* inputs; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t INA3221_CHANNEL3 ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t,...) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,size_t*) ; 

__attribute__((used)) static int ina3221_probe_child_from_dt(struct device *dev,
				       struct device_node *child,
				       struct ina3221_data *ina)
{
	struct ina3221_input *input;
	u32 val;
	int ret;

	ret = of_property_read_u32(child, "reg", &val);
	if (ret) {
		dev_err(dev, "missing reg property of %pOFn\n", child);
		return ret;
	} else if (val > INA3221_CHANNEL3) {
		dev_err(dev, "invalid reg %d of %pOFn\n", val, child);
		return ret;
	}

	input = &ina->inputs[val];

	/* Log the disconnected channel input */
	if (!of_device_is_available(child)) {
		input->disconnected = true;
		return 0;
	}

	/* Save the connected input label if available */
	of_property_read_string(child, "label", &input->label);

	/* Overwrite default shunt resistor value optionally */
	if (!of_property_read_u32(child, "shunt-resistor-micro-ohms", &val)) {
		if (val < 1 || val > INT_MAX) {
			dev_err(dev, "invalid shunt resistor value %u of %pOFn\n",
				val, child);
			return -EINVAL;
		}
		input->shunt_resistor = val;
	}

	return 0;
}