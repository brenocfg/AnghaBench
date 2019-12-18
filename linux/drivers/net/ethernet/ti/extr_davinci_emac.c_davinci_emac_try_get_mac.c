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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ti_cm_get_macid (TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int davinci_emac_try_get_mac(struct platform_device *pdev,
				    int instance, u8 *mac_addr)
{
	if (!pdev->dev.of_node)
		return -EINVAL;

	return ti_cm_get_macid(&pdev->dev, instance, mac_addr);
}