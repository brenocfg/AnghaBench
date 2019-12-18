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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct meson_canvas {int /*<<< orphan*/  lock; struct device* dev; int /*<<< orphan*/  supports_endianness; int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct meson_canvas*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct meson_canvas* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meson_canvas_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct meson_canvas *canvas;
	struct device *dev = &pdev->dev;

	canvas = devm_kzalloc(dev, sizeof(*canvas), GFP_KERNEL);
	if (!canvas)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	canvas->reg_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(canvas->reg_base))
		return PTR_ERR(canvas->reg_base);

	canvas->supports_endianness = of_device_get_match_data(dev);

	canvas->dev = dev;
	spin_lock_init(&canvas->lock);
	dev_set_drvdata(dev, canvas);

	return 0;
}