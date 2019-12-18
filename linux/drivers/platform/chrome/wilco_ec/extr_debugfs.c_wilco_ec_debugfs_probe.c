#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wilco_ec_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dir; struct wilco_ec_device* ec; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* debug_info ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct wilco_ec_device*,int /*<<< orphan*/ *) ; 
 struct wilco_ec_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fops_h1_gpio ; 
 int /*<<< orphan*/  fops_raw ; 

__attribute__((used)) static int wilco_ec_debugfs_probe(struct platform_device *pdev)
{
	struct wilco_ec_device *ec = dev_get_drvdata(pdev->dev.parent);

	debug_info = devm_kzalloc(&pdev->dev, sizeof(*debug_info), GFP_KERNEL);
	if (!debug_info)
		return 0;
	debug_info->ec = ec;
	debug_info->dir = debugfs_create_dir("wilco_ec", NULL);
	if (!debug_info->dir)
		return 0;
	debugfs_create_file("raw", 0644, debug_info->dir, NULL, &fops_raw);
	debugfs_create_file("h1_gpio", 0444, debug_info->dir, ec,
			    &fops_h1_gpio);

	return 0;
}