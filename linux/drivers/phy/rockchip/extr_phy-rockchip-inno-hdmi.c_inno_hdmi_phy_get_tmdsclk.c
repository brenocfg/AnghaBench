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
typedef  int u64 ;
struct inno_hdmi_phy {int /*<<< orphan*/  phy; } ;

/* Variables and functions */
 int phy_get_bus_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long inno_hdmi_phy_get_tmdsclk(struct inno_hdmi_phy *inno,
					       unsigned long rate)
{
	int bus_width = phy_get_bus_width(inno->phy);

	switch (bus_width) {
	case 4:
	case 5:
	case 6:
	case 10:
	case 12:
	case 16:
		return (u64)rate * bus_width / 8;
	default:
		return rate;
	}
}