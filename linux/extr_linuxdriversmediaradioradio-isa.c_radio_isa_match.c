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
struct radio_isa_driver {scalar_t__* io_params; scalar_t__ probe; } ;
struct device {struct radio_isa_driver* platform_data; } ;

/* Variables and functions */

int radio_isa_match(struct device *pdev, unsigned int dev)
{
	struct radio_isa_driver *drv = pdev->platform_data;

	return drv->probe || drv->io_params[dev] >= 0;
}