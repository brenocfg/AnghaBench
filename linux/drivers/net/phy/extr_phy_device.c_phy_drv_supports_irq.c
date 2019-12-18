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
struct phy_driver {scalar_t__ ack_interrupt; scalar_t__ config_intr; } ;

/* Variables and functions */

__attribute__((used)) static bool phy_drv_supports_irq(struct phy_driver *phydrv)
{
	return phydrv->config_intr && phydrv->ack_interrupt;
}