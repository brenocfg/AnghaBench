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
struct device {TYPE_1__* of_node; } ;
struct platform_device {struct device dev; } ;
struct lantiq_rcu_reset_priv {void* status_offset; void* reset_offset; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* __be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/ * of_get_address (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lantiq_rcu_reset_of_parse(struct platform_device *pdev,
			       struct lantiq_rcu_reset_priv *priv)
{
	struct device *dev = &pdev->dev;
	const __be32 *offset;

	priv->regmap = syscon_node_to_regmap(dev->of_node->parent);
	if (IS_ERR(priv->regmap)) {
		dev_err(&pdev->dev, "Failed to lookup RCU regmap\n");
		return PTR_ERR(priv->regmap);
	}

	offset = of_get_address(dev->of_node, 0, NULL, NULL);
	if (!offset) {
		dev_err(&pdev->dev, "Failed to get RCU reset offset\n");
		return -ENOENT;
	}
	priv->reset_offset = __be32_to_cpu(*offset);

	offset = of_get_address(dev->of_node, 1, NULL, NULL);
	if (!offset) {
		dev_err(&pdev->dev, "Failed to get RCU status offset\n");
		return -ENOENT;
	}
	priv->status_offset = __be32_to_cpu(*offset);

	return 0;
}