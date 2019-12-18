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
struct nozomi {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_card_type ; 
 int /*<<< orphan*/  dev_attr_open_ttys ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void make_sysfs_files(struct nozomi *dc)
{
	if (device_create_file(&dc->pdev->dev, &dev_attr_card_type))
		dev_err(&dc->pdev->dev,
			"Could not create sysfs file for card_type\n");
	if (device_create_file(&dc->pdev->dev, &dev_attr_open_ttys))
		dev_err(&dc->pdev->dev,
			"Could not create sysfs file for open_ttys\n");
}