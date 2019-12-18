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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct mdio_mux_multiplexer_state {int /*<<< orphan*/  mux_handle; int /*<<< orphan*/  muxc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct mdio_mux_multiplexer_state* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_mux_control_get (struct device*,int /*<<< orphan*/ *) ; 
 int mdio_mux_init (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdio_mux_multiplexer_switch_fn ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mdio_mux_multiplexer_state*) ; 

__attribute__((used)) static int mdio_mux_multiplexer_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mdio_mux_multiplexer_state *s;
	int ret = 0;

	s = devm_kzalloc(&pdev->dev, sizeof(*s), GFP_KERNEL);
	if (!s)
		return -ENOMEM;

	s->muxc = devm_mux_control_get(dev, NULL);
	if (IS_ERR(s->muxc)) {
		ret = PTR_ERR(s->muxc);
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to get mux: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, s);

	ret = mdio_mux_init(&pdev->dev, pdev->dev.of_node,
			    mdio_mux_multiplexer_switch_fn, &s->mux_handle,
			    pdev, NULL);

	return ret;
}