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
typedef  scalar_t__ u32 ;
struct rockchip_thermal_data {int tshut_mode; int tshut_polarity; int /*<<< orphan*/  grf; TYPE_1__* chip; scalar_t__ tshut_temp; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ tshut_mode; scalar_t__ tshut_polarity; scalar_t__ tshut_temp; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ TSHUT_LOW_ACTIVE ; 
 scalar_t__ TSHUT_MODE_GPIO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int rockchip_configure_from_dt(struct device *dev,
				      struct device_node *np,
				      struct rockchip_thermal_data *thermal)
{
	u32 shut_temp, tshut_mode, tshut_polarity;

	if (of_property_read_u32(np, "rockchip,hw-tshut-temp", &shut_temp)) {
		dev_warn(dev,
			 "Missing tshut temp property, using default %d\n",
			 thermal->chip->tshut_temp);
		thermal->tshut_temp = thermal->chip->tshut_temp;
	} else {
		if (shut_temp > INT_MAX) {
			dev_err(dev, "Invalid tshut temperature specified: %d\n",
				shut_temp);
			return -ERANGE;
		}
		thermal->tshut_temp = shut_temp;
	}

	if (of_property_read_u32(np, "rockchip,hw-tshut-mode", &tshut_mode)) {
		dev_warn(dev,
			 "Missing tshut mode property, using default (%s)\n",
			 thermal->chip->tshut_mode == TSHUT_MODE_GPIO ?
				"gpio" : "cru");
		thermal->tshut_mode = thermal->chip->tshut_mode;
	} else {
		thermal->tshut_mode = tshut_mode;
	}

	if (thermal->tshut_mode > 1) {
		dev_err(dev, "Invalid tshut mode specified: %d\n",
			thermal->tshut_mode);
		return -EINVAL;
	}

	if (of_property_read_u32(np, "rockchip,hw-tshut-polarity",
				 &tshut_polarity)) {
		dev_warn(dev,
			 "Missing tshut-polarity property, using default (%s)\n",
			 thermal->chip->tshut_polarity == TSHUT_LOW_ACTIVE ?
				"low" : "high");
		thermal->tshut_polarity = thermal->chip->tshut_polarity;
	} else {
		thermal->tshut_polarity = tshut_polarity;
	}

	if (thermal->tshut_polarity > 1) {
		dev_err(dev, "Invalid tshut-polarity specified: %d\n",
			thermal->tshut_polarity);
		return -EINVAL;
	}

	/* The tsadc wont to handle the error in here since some SoCs didn't
	 * need this property.
	 */
	thermal->grf = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	if (IS_ERR(thermal->grf))
		dev_warn(dev, "Missing rockchip,grf property\n");

	return 0;
}