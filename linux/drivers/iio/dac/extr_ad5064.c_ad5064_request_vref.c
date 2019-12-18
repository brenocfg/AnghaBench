#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct ad5064_state {int use_internal_vref; TYPE_2__* vref_reg; TYPE_1__* chip_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  consumer; int /*<<< orphan*/  supply; } ;
struct TYPE_3__ {int /*<<< orphan*/  internal_vref; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5064_CONFIG_INT_VREF_ENABLE ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 unsigned int ad5064_num_vref (struct ad5064_state*) ; 
 int ad5064_set_config (struct ad5064_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad5064_vref_name (struct ad5064_state*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int devm_regulator_bulk_get (struct device*,unsigned int,TYPE_2__*) ; 
 int /*<<< orphan*/  devm_regulator_get_optional (struct device*,char*) ; 

__attribute__((used)) static int ad5064_request_vref(struct ad5064_state *st, struct device *dev)
{
	unsigned int i;
	int ret;

	for (i = 0; i < ad5064_num_vref(st); ++i)
		st->vref_reg[i].supply = ad5064_vref_name(st, i);

	if (!st->chip_info->internal_vref)
		return devm_regulator_bulk_get(dev, ad5064_num_vref(st),
					       st->vref_reg);

	/*
	 * This assumes that when the regulator has an internal VREF
	 * there is only one external VREF connection, which is
	 * currently the case for all supported devices.
	 */
	st->vref_reg[0].consumer = devm_regulator_get_optional(dev, "vref");
	if (!IS_ERR(st->vref_reg[0].consumer))
		return 0;

	ret = PTR_ERR(st->vref_reg[0].consumer);
	if (ret != -ENODEV)
		return ret;

	/* If no external regulator was supplied use the internal VREF */
	st->use_internal_vref = true;
	ret = ad5064_set_config(st, AD5064_CONFIG_INT_VREF_ENABLE);
	if (ret)
		dev_err(dev, "Failed to enable internal vref: %d\n", ret);

	return ret;
}