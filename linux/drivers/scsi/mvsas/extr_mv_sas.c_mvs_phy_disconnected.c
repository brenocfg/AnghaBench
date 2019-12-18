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
struct mvs_phy {scalar_t__ att_dev_sas_addr; scalar_t__ att_dev_info; scalar_t__ phy_attached; } ;

/* Variables and functions */

__attribute__((used)) static void mvs_phy_disconnected(struct mvs_phy *phy)
{
	phy->phy_attached = 0;
	phy->att_dev_info = 0;
	phy->att_dev_sas_addr = 0;
}