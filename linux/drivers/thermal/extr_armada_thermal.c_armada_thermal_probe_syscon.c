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
struct TYPE_4__ {TYPE_1__* parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct armada_thermal_priv {int /*<<< orphan*/  syscon; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada_thermal_probe_syscon(struct platform_device *pdev,
				       struct armada_thermal_priv *priv)
{
	priv->syscon = syscon_node_to_regmap(pdev->dev.parent->of_node);
	return PTR_ERR_OR_ZERO(priv->syscon);
}