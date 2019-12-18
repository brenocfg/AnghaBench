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
typedef  int u32 ;
struct TYPE_2__ {int scanning_period; int debounce_timeout; int settling_timeout; int touch_timeout; int average_data; int fifo_threshold; int max_x; int max_y; int fuzz_x; int fuzz_y; void* invert_y; void* invert_x; } ;
struct iproc_ts_priv {TYPE_1__ cfg_params; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 TYPE_1__ iproc_default_config ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int iproc_get_tsc_config(struct device *dev, struct iproc_ts_priv *priv)
{
	struct device_node *np = dev->of_node;
	u32 val;

	priv->cfg_params = iproc_default_config;

	if (!np)
		return 0;

	if (of_property_read_u32(np, "scanning_period", &val) >= 0) {
		if (val < 1 || val > 256) {
			dev_err(dev, "scanning_period (%u) must be [1-256]\n",
				val);
			return -EINVAL;
		}
		priv->cfg_params.scanning_period = val;
	}

	if (of_property_read_u32(np, "debounce_timeout", &val) >= 0) {
		if (val > 255) {
			dev_err(dev, "debounce_timeout (%u) must be [0-255]\n",
				val);
			return -EINVAL;
		}
		priv->cfg_params.debounce_timeout = val;
	}

	if (of_property_read_u32(np, "settling_timeout", &val) >= 0) {
		if (val > 11) {
			dev_err(dev, "settling_timeout (%u) must be [0-11]\n",
				val);
			return -EINVAL;
		}
		priv->cfg_params.settling_timeout = val;
	}

	if (of_property_read_u32(np, "touch_timeout", &val) >= 0) {
		if (val > 255) {
			dev_err(dev, "touch_timeout (%u) must be [0-255]\n",
				val);
			return -EINVAL;
		}
		priv->cfg_params.touch_timeout = val;
	}

	if (of_property_read_u32(np, "average_data", &val) >= 0) {
		if (val > 8) {
			dev_err(dev, "average_data (%u) must be [0-8]\n", val);
			return -EINVAL;
		}
		priv->cfg_params.average_data = val;
	}

	if (of_property_read_u32(np, "fifo_threshold", &val) >= 0) {
		if (val > 31) {
			dev_err(dev, "fifo_threshold (%u)) must be [0-31]\n",
				val);
			return -EINVAL;
		}
		priv->cfg_params.fifo_threshold = val;
	}

	/* Parse optional properties. */
	of_property_read_u32(np, "touchscreen-size-x", &priv->cfg_params.max_x);
	of_property_read_u32(np, "touchscreen-size-y", &priv->cfg_params.max_y);

	of_property_read_u32(np, "touchscreen-fuzz-x",
			     &priv->cfg_params.fuzz_x);
	of_property_read_u32(np, "touchscreen-fuzz-y",
			     &priv->cfg_params.fuzz_y);

	priv->cfg_params.invert_x =
		of_property_read_bool(np, "touchscreen-inverted-x");
	priv->cfg_params.invert_y =
		of_property_read_bool(np, "touchscreen-inverted-y");

	return 0;
}