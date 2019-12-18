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
struct wcnss_vreg_info {scalar_t__ load_uA; scalar_t__ max_voltage; int /*<<< orphan*/  min_voltage; int /*<<< orphan*/  name; } ;
struct regulator_bulk_data {int /*<<< orphan*/  consumer; int /*<<< orphan*/  supply; } ;
struct qcom_wcnss {int num_vregs; struct regulator_bulk_data* vregs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct regulator_bulk_data* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ ,int,struct regulator_bulk_data*) ; 
 int /*<<< orphan*/  regulator_set_load (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  regulator_set_voltage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int wcnss_init_regulators(struct qcom_wcnss *wcnss,
				 const struct wcnss_vreg_info *info,
				 int num_vregs)
{
	struct regulator_bulk_data *bulk;
	int ret;
	int i;

	bulk = devm_kcalloc(wcnss->dev,
			    num_vregs, sizeof(struct regulator_bulk_data),
			    GFP_KERNEL);
	if (!bulk)
		return -ENOMEM;

	for (i = 0; i < num_vregs; i++)
		bulk[i].supply = info[i].name;

	ret = devm_regulator_bulk_get(wcnss->dev, num_vregs, bulk);
	if (ret)
		return ret;

	for (i = 0; i < num_vregs; i++) {
		if (info[i].max_voltage)
			regulator_set_voltage(bulk[i].consumer,
					      info[i].min_voltage,
					      info[i].max_voltage);

		if (info[i].load_uA)
			regulator_set_load(bulk[i].consumer, info[i].load_uA);
	}

	wcnss->vregs = bulk;
	wcnss->num_vregs = num_vregs;

	return 0;
}