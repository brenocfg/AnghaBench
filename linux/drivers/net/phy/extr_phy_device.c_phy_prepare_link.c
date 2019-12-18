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
struct phy_device {void (* adjust_link ) (struct net_device*) ;} ;

/* Variables and functions */

__attribute__((used)) static void phy_prepare_link(struct phy_device *phydev,
			     void (*handler)(struct net_device *))
{
	phydev->adjust_link = handler;
}