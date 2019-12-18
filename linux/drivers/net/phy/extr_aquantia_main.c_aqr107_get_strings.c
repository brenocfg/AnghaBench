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
typedef  int /*<<< orphan*/  u8 ;
struct phy_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AQR107_SGMII_STAT_SZ ; 
 int ETH_GSTRING_LEN ; 
 TYPE_1__* aqr107_hw_stats ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aqr107_get_strings(struct phy_device *phydev, u8 *data)
{
	int i;

	for (i = 0; i < AQR107_SGMII_STAT_SZ; i++)
		strscpy(data + i * ETH_GSTRING_LEN, aqr107_hw_stats[i].name,
			ETH_GSTRING_LEN);
}