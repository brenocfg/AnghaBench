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
typedef  int /*<<< orphan*/  u64 ;
struct phy_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIN1300_RX_ERR_CNT ; 
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adin_get_stat (struct phy_device*,int) ; 
 int /*<<< orphan*/  adin_hw_stats ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adin_get_stats(struct phy_device *phydev,
			   struct ethtool_stats *stats, u64 *data)
{
	int i, rc;

	/* latch copies of all the frame-checker counters */
	rc = phy_read(phydev, ADIN1300_RX_ERR_CNT);
	if (rc < 0)
		return;

	for (i = 0; i < ARRAY_SIZE(adin_hw_stats); i++)
		data[i] = adin_get_stat(phydev, i);
}