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
typedef  scalar_t__ u16 ;
struct r8152 {int dummy; } ;

/* Variables and functions */
 scalar_t__ ABD_STATE ; 
 int /*<<< orphan*/  OCP_PHY_STATE ; 
 scalar_t__ TXDIS_STATE ; 
 int ocp_reg_read (struct r8152*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rtl8153_in_nway(struct r8152 *tp)
{
	u16 phy_state = ocp_reg_read(tp, OCP_PHY_STATE) & 0xff;

	if (phy_state == TXDIS_STATE || phy_state == ABD_STATE)
		return false;
	else
		return true;
}