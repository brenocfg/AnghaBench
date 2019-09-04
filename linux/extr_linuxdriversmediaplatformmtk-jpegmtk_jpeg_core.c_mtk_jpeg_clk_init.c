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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mtk_jpeg_dev {void* clk_jdec_smi; TYPE_1__* dev; void* clk_jdec; int /*<<< orphan*/ * larb; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 scalar_t__ WARN_ON (int) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_jpeg_clk_init(struct mtk_jpeg_dev *jpeg)
{
	struct device_node *node;
	struct platform_device *pdev;

	node = of_parse_phandle(jpeg->dev->of_node, "mediatek,larb", 0);
	if (!node)
		return -EINVAL;
	pdev = of_find_device_by_node(node);
	if (WARN_ON(!pdev)) {
		of_node_put(node);
		return -EINVAL;
	}
	of_node_put(node);

	jpeg->larb = &pdev->dev;

	jpeg->clk_jdec = devm_clk_get(jpeg->dev, "jpgdec");
	if (IS_ERR(jpeg->clk_jdec))
		return PTR_ERR(jpeg->clk_jdec);

	jpeg->clk_jdec_smi = devm_clk_get(jpeg->dev, "jpgdec-smi");
	return PTR_ERR_OR_ZERO(jpeg->clk_jdec_smi);
}