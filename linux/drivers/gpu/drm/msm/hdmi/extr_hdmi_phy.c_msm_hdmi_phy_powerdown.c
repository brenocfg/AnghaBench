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
struct hdmi_phy {TYPE_1__* cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* powerdown ) (struct hdmi_phy*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hdmi_phy*) ; 

void msm_hdmi_phy_powerdown(struct hdmi_phy *phy)
{
	if (!phy || !phy->cfg->powerdown)
		return;

	phy->cfg->powerdown(phy);
}