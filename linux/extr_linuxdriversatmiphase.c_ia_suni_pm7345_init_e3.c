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
typedef  int u32 ;
struct iadev_priv {int carrier_detect; } ;
struct ia_reg {int member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ia_reg const*) ; 
#define  SUNI_CONFIG 137 
#define  SUNI_E3_FRM_FRAM_INTR_ENBL 136 
 int /*<<< orphan*/  SUNI_E3_FRM_FRAM_INTR_IND_STAT ; 
#define  SUNI_E3_FRM_FRAM_OPTIONS 135 
#define  SUNI_E3_FRM_MAINT_INTR_ENBL 134 
#define  SUNI_E3_FRM_MAINT_OPTIONS 133 
 int SUNI_E3_LOS ; 
#define  SUNI_E3_TRAN_FRAM_OPTIONS 132 
#define  SUNI_E3_TRAN_STAT_DIAG_OPTIONS 131 
#define  SUNI_PM7345_E3ENBL 130 
#define  SUNI_SPLR_CFG 129 
#define  SUNI_SPLT_CFG 128 
 int ia_phy_read32 (struct iadev_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia_phy_write (struct iadev_priv*,struct ia_reg const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ia_suni_pm7345_init_e3(struct iadev_priv *iadev)
{
	static const struct ia_reg suni_e3_init[] = {
		{ SUNI_E3_FRM_FRAM_OPTIONS,		0x04 },
		{ SUNI_E3_FRM_MAINT_OPTIONS,		0x20 },
		{ SUNI_E3_FRM_FRAM_INTR_ENBL,		0x1d },
		{ SUNI_E3_FRM_MAINT_INTR_ENBL,		0x30 },
		{ SUNI_E3_TRAN_STAT_DIAG_OPTIONS,	0 },
		{ SUNI_E3_TRAN_FRAM_OPTIONS,		0x01 },
		{ SUNI_CONFIG,				SUNI_PM7345_E3ENBL },
		{ SUNI_SPLR_CFG,			0x41 },
		{ SUNI_SPLT_CFG,			0x41 }
	};
	u32 status;

	status = ia_phy_read32(iadev, SUNI_E3_FRM_FRAM_INTR_IND_STAT);
	iadev->carrier_detect = (status & SUNI_E3_LOS) ? 0 : 1;
	ia_phy_write(iadev, suni_e3_init, ARRAY_SIZE(suni_e3_init));
}