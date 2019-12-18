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
struct igbvf_adapter {scalar_t__ link_duplex; int /*<<< orphan*/  link_speed; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ FULL_DUPLEX ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void igbvf_print_link_info(struct igbvf_adapter *adapter)
{
	dev_info(&adapter->pdev->dev, "Link is Up %d Mbps %s Duplex\n",
		 adapter->link_speed,
		 adapter->link_duplex == FULL_DUPLEX ? "Full" : "Half");
}