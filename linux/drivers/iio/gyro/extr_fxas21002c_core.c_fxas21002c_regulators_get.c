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
struct fxas21002c_data {void* vddio; void* vdd; int /*<<< orphan*/  regmap; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 void* devm_regulator_get (int /*<<< orphan*/ ,char*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fxas21002c_regulators_get(struct fxas21002c_data *data)
{
	struct device *dev = regmap_get_device(data->regmap);

	data->vdd = devm_regulator_get(dev->parent, "vdd");
	if (IS_ERR(data->vdd))
		return PTR_ERR(data->vdd);

	data->vddio = devm_regulator_get(dev->parent, "vddio");

	return PTR_ERR_OR_ZERO(data->vddio);
}