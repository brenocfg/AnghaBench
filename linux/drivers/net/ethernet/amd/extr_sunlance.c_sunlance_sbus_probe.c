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
struct TYPE_2__ {struct device_node* of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ of_node_name_eq (struct device_node*,char*) ; 
 int sparc_lance_probe_one (struct platform_device*,struct platform_device*,struct platform_device*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunlance_sbus_probe(struct platform_device *op)
{
	struct platform_device *parent = to_platform_device(op->dev.parent);
	struct device_node *parent_dp = parent->dev.of_node;
	int err;

	if (of_node_name_eq(parent_dp, "ledma")) {
		err = sparc_lance_probe_one(op, parent, NULL);
	} else if (of_node_name_eq(parent_dp, "lebuffer")) {
		err = sparc_lance_probe_one(op, NULL, parent);
	} else
		err = sparc_lance_probe_one(op, NULL, NULL);

	return err;
}