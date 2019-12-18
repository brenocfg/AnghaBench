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
struct gbe_slave {TYPE_1__* phy; } ;
struct TYPE_2__ {scalar_t__ link; } ;

/* Variables and functions */

__attribute__((used)) static bool gbe_phy_link_status(struct gbe_slave *slave)
{
	 return !slave->phy || slave->phy->link;
}