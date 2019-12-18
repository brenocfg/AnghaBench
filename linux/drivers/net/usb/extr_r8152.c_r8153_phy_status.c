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
typedef  int u16 ;
struct r8152 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCP_PHY_STATUS ; 
 int PHY_STAT_EXT_INIT ; 
 int PHY_STAT_LAN_ON ; 
 int PHY_STAT_MASK ; 
 int PHY_STAT_PWRDN ; 
 int /*<<< orphan*/  msleep (int) ; 
 int ocp_reg_read (struct r8152*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 r8153_phy_status(struct r8152 *tp, u16 desired)
{
	u16 data;
	int i;

	for (i = 0; i < 500; i++) {
		data = ocp_reg_read(tp, OCP_PHY_STATUS);
		data &= PHY_STAT_MASK;
		if (desired) {
			if (data == desired)
				break;
		} else if (data == PHY_STAT_LAN_ON || data == PHY_STAT_PWRDN ||
			   data == PHY_STAT_EXT_INIT) {
			break;
		}

		msleep(20);
	}

	return data;
}