#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;
struct xvtc_device {TYPE_1__ xvip; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct xvtc_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xvtc_device*) ; 
 int xvip_init_resources (TYPE_1__*) ; 
 int /*<<< orphan*/  xvip_print_version (TYPE_1__*) ; 
 int xvtc_parse_of (struct xvtc_device*) ; 
 int /*<<< orphan*/  xvtc_register_device (struct xvtc_device*) ; 

__attribute__((used)) static int xvtc_probe(struct platform_device *pdev)
{
	struct xvtc_device *xvtc;
	int ret;

	xvtc = devm_kzalloc(&pdev->dev, sizeof(*xvtc), GFP_KERNEL);
	if (!xvtc)
		return -ENOMEM;

	xvtc->xvip.dev = &pdev->dev;

	ret = xvtc_parse_of(xvtc);
	if (ret < 0)
		return ret;

	ret = xvip_init_resources(&xvtc->xvip);
	if (ret < 0)
		return ret;

	platform_set_drvdata(pdev, xvtc);

	xvip_print_version(&xvtc->xvip);

	xvtc_register_device(xvtc);

	return 0;
}