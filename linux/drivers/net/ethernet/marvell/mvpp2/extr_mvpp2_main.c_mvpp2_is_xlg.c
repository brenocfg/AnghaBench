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
typedef  scalar_t__ phy_interface_t ;

/* Variables and functions */
 scalar_t__ PHY_INTERFACE_MODE_10GKR ; 
 scalar_t__ PHY_INTERFACE_MODE_XAUI ; 

__attribute__((used)) static bool mvpp2_is_xlg(phy_interface_t interface)
{
	return interface == PHY_INTERFACE_MODE_10GKR ||
	       interface == PHY_INTERFACE_MODE_XAUI;
}