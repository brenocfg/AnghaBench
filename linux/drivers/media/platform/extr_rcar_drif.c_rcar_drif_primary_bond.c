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

/* Variables and functions */
 int of_property_read_bool (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool rcar_drif_primary_bond(struct platform_device *pdev)
{
	return of_property_read_bool(pdev->dev.of_node, "renesas,primary-bond");
}