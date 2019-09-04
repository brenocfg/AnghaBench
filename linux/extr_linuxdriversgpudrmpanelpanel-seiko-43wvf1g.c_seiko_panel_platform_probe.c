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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENODEV ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_of_match ; 
 int seiko_panel_probe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seiko_panel_platform_probe(struct platform_device *pdev)
{
	const struct of_device_id *id;

	id = of_match_node(platform_of_match, pdev->dev.of_node);
	if (!id)
		return -ENODEV;

	return seiko_panel_probe(&pdev->dev, id->data);
}