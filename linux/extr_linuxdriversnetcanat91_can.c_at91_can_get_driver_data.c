#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct at91_devtype_data {int dummy; } ;
struct TYPE_3__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91_can_dt_ids ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* platform_get_device_id (struct platform_device*) ; 

__attribute__((used)) static const struct at91_devtype_data *at91_can_get_driver_data(struct platform_device *pdev)
{
	if (pdev->dev.of_node) {
		const struct of_device_id *match;

		match = of_match_node(at91_can_dt_ids, pdev->dev.of_node);
		if (!match) {
			dev_err(&pdev->dev, "no matching node found in dtb\n");
			return NULL;
		}
		return (const struct at91_devtype_data *)match->data;
	}
	return (const struct at91_devtype_data *)
		platform_get_device_id(pdev)->driver_data;
}