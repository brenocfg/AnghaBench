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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  TI_XBAR_AM335X 129 
#define  TI_XBAR_DRA7 128 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ti_am335x_xbar_probe (struct platform_device*) ; 
 int /*<<< orphan*/  ti_dma_xbar_match ; 
 int ti_dra7_xbar_probe (struct platform_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ti_dma_xbar_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	int ret;

	match = of_match_node(ti_dma_xbar_match, pdev->dev.of_node);
	if (unlikely(!match))
		return -EINVAL;

	switch (*(u32 *)match->data) {
	case TI_XBAR_DRA7:
		ret = ti_dra7_xbar_probe(pdev);
		break;
	case TI_XBAR_AM335X:
		ret = ti_am335x_xbar_probe(pdev);
		break;
	default:
		dev_err(&pdev->dev, "Unsupported crossbar\n");
		ret = -ENODEV;
		break;
	}

	return ret;
}