#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;
struct device {TYPE_3__* parent; } ;
struct TYPE_5__ {TYPE_1__* caps; struct device* dev; } ;
struct atmel_smc_nand_controller {uintptr_t ebi_csa_offs; int /*<<< orphan*/  matrix; TYPE_2__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {scalar_t__ legacy_of_bindings; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_matrix_of_ids ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static int
atmel_smc_nand_controller_init(struct atmel_smc_nand_controller *nc)
{
	struct device *dev = nc->base.dev;
	const struct of_device_id *match;
	struct device_node *np;
	int ret;

	/* We do not retrieve the matrix syscon when parsing old DTs. */
	if (nc->base.caps->legacy_of_bindings)
		return 0;

	np = of_parse_phandle(dev->parent->of_node, "atmel,matrix", 0);
	if (!np)
		return 0;

	match = of_match_node(atmel_matrix_of_ids, np);
	if (!match) {
		of_node_put(np);
		return 0;
	}

	nc->matrix = syscon_node_to_regmap(np);
	of_node_put(np);
	if (IS_ERR(nc->matrix)) {
		ret = PTR_ERR(nc->matrix);
		dev_err(dev, "Could not get Matrix regmap (err = %d)\n", ret);
		return ret;
	}

	nc->ebi_csa_offs = (uintptr_t)match->data;

	/*
	 * The at91sam9263 has 2 EBIs, if the NAND controller is under EBI1
	 * add 4 to ->ebi_csa_offs.
	 */
	if (of_device_is_compatible(dev->parent->of_node,
				    "atmel,at91sam9263-ebi1"))
		nc->ebi_csa_offs += 4;

	return 0;
}