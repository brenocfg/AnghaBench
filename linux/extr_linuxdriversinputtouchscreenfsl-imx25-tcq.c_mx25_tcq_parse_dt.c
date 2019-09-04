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
typedef  int u32 ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mx25_tcq_priv {int pen_threshold; int sample_count; int pen_debounce; int settling_time; int /*<<< orphan*/  mode; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MX25_TS_4WIRE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int mx25_tcq_parse_dt(struct platform_device *pdev,
			     struct mx25_tcq_priv *priv)
{
	struct device_node *np = pdev->dev.of_node;
	u32 wires;
	int error;

	/* Setup defaults */
	priv->pen_threshold = 500;
	priv->sample_count = 3;
	priv->pen_debounce = 1000000;
	priv->settling_time = 250000;

	error = of_property_read_u32(np, "fsl,wires", &wires);
	if (error) {
		dev_err(&pdev->dev, "Failed to find fsl,wires properties\n");
		return error;
	}

	if (wires == 4) {
		priv->mode = MX25_TS_4WIRE;
	} else {
		dev_err(&pdev->dev, "%u-wire mode not supported\n", wires);
		return -EINVAL;
	}

	/* These are optional, we don't care about the return values */
	of_property_read_u32(np, "fsl,pen-threshold", &priv->pen_threshold);
	of_property_read_u32(np, "fsl,settling-time-ns", &priv->settling_time);
	of_property_read_u32(np, "fsl,pen-debounce-ns", &priv->pen_debounce);

	return 0;
}