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
struct ql3_adapter {int phyType; } ;

/* Variables and functions */
 int AUX_CONTROL_STATUS ; 
#define  PHY_AGERE_ET1011C 129 
 int PHY_AUX_DUPLEX_STAT ; 
#define  PHY_VITESSE_VSC8211 128 
 int /*<<< orphan*/  ql_mii_read_reg (struct ql3_adapter*,int,int*) ; 

__attribute__((used)) static int ql_is_full_dup(struct ql3_adapter *qdev)
{
	u16 reg;

	switch (qdev->phyType) {
	case PHY_AGERE_ET1011C: {
		if (ql_mii_read_reg(qdev, 0x1A, &reg))
			return 0;

		return ((reg & 0x0080) && (reg & 0x1000)) != 0;
	}
	case PHY_VITESSE_VSC8211:
	default: {
		if (ql_mii_read_reg(qdev, AUX_CONTROL_STATUS, &reg) < 0)
			return 0;
		return (reg & PHY_AUX_DUPLEX_STAT) != 0;
	}
	}
}