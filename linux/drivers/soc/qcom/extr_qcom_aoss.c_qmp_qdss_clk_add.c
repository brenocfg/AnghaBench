#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct clk_init_data const* init; } ;
struct qmp {TYPE_1__ qdss_clk; TYPE_2__* dev; } ;
struct clk_init_data {char* name; int /*<<< orphan*/ * ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int clk_hw_register (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  clk_hw_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int of_clk_add_hw_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_clk_hw_simple_get ; 
 int /*<<< orphan*/  qmp_qdss_clk_ops ; 

__attribute__((used)) static int qmp_qdss_clk_add(struct qmp *qmp)
{
	static const struct clk_init_data qdss_init = {
		.ops = &qmp_qdss_clk_ops,
		.name = "qdss",
	};
	int ret;

	qmp->qdss_clk.init = &qdss_init;
	ret = clk_hw_register(qmp->dev, &qmp->qdss_clk);
	if (ret < 0) {
		dev_err(qmp->dev, "failed to register qdss clock\n");
		return ret;
	}

	ret = of_clk_add_hw_provider(qmp->dev->of_node, of_clk_hw_simple_get,
				     &qmp->qdss_clk);
	if (ret < 0) {
		dev_err(qmp->dev, "unable to register of clk hw provider\n");
		clk_hw_unregister(&qmp->qdss_clk);
	}

	return ret;
}