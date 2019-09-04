#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {unsigned long* supported; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclge_dev {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseSR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseX_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_25000baseSR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_FIBRE_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Pause_BIT ; 
 int HCLGE_SUPPORT_100G_BIT ; 
 int HCLGE_SUPPORT_10G_BIT ; 
 int HCLGE_SUPPORT_1G_BIT ; 
 int HCLGE_SUPPORT_25G_BIT ; 
 int HCLGE_SUPPORT_50G_BIT ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void hclge_parse_fiber_link_mode(struct hclge_dev *hdev,
					u8 speed_ability)
{
	unsigned long *supported = hdev->hw.mac.supported;

	if (speed_ability & HCLGE_SUPPORT_1G_BIT)
		set_bit(ETHTOOL_LINK_MODE_1000baseX_Full_BIT,
			supported);

	if (speed_ability & HCLGE_SUPPORT_10G_BIT)
		set_bit(ETHTOOL_LINK_MODE_10000baseSR_Full_BIT,
			supported);

	if (speed_ability & HCLGE_SUPPORT_25G_BIT)
		set_bit(ETHTOOL_LINK_MODE_25000baseSR_Full_BIT,
			supported);

	if (speed_ability & HCLGE_SUPPORT_50G_BIT)
		set_bit(ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT,
			supported);

	if (speed_ability & HCLGE_SUPPORT_100G_BIT)
		set_bit(ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT,
			supported);

	set_bit(ETHTOOL_LINK_MODE_FIBRE_BIT, supported);
	set_bit(ETHTOOL_LINK_MODE_Pause_BIT, supported);
}