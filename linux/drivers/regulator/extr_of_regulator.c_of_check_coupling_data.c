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
struct TYPE_4__ {struct device_node* of_node; } ;
struct regulator_dev {TYPE_2__ dev; TYPE_1__* constraints; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int* max_spread; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int of_count_phandle_with_args (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_coupling_find_node (struct device_node*,struct device_node*,int*) ; 
 int of_get_n_coupled (struct regulator_dev*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int) ; 
 scalar_t__ of_property_read_u32_index (struct device_node*,char*,int,int*) ; 

bool of_check_coupling_data(struct regulator_dev *rdev)
{
	struct device_node *node = rdev->dev.of_node;
	int n_phandles = of_get_n_coupled(rdev);
	struct device_node *c_node;
	int index;
	int i;
	bool ret = true;

	/* iterate over rdev's phandles */
	for (i = 0; i < n_phandles; i++) {
		int max_spread = rdev->constraints->max_spread[i];
		int c_max_spread, c_n_phandles;

		if (max_spread <= 0) {
			dev_err(&rdev->dev, "max_spread value invalid\n");
			return false;
		}

		c_node = of_parse_phandle(node,
					  "regulator-coupled-with", i);

		if (!c_node)
			ret = false;

		c_n_phandles = of_count_phandle_with_args(c_node,
							  "regulator-coupled-with",
							  NULL);

		if (c_n_phandles != n_phandles) {
			dev_err(&rdev->dev, "number of coupled reg phandles mismatch\n");
			ret = false;
			goto clean;
		}

		if (!of_coupling_find_node(c_node, node, &index)) {
			dev_err(&rdev->dev, "missing 2-way linking for coupled regulators\n");
			ret = false;
			goto clean;
		}

		if (of_property_read_u32_index(c_node, "regulator-coupled-max-spread",
					       index, &c_max_spread)) {
			ret = false;
			goto clean;
		}

		if (c_max_spread != max_spread) {
			dev_err(&rdev->dev,
				"coupled regulators max_spread mismatch\n");
			ret = false;
			goto clean;
		}

clean:
		of_node_put(c_node);
		if (!ret)
			break;
	}

	return ret;
}