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
typedef  int u32 ;
struct mvs_info {TYPE_1__* pdev; } ;
struct ffe_control {int ffe_rss_sel; int ffe_cap_sel; } ;
struct TYPE_2__ {scalar_t__ revision; } ;

/* Variables and functions */
 scalar_t__ VANIR_A0_REV ; 
 scalar_t__ VANIR_B0_REV ; 
 int /*<<< orphan*/  VSR_PHY_DFE_UPDATE_CRTL ; 
 int /*<<< orphan*/  VSR_PHY_FFE_CONTROL ; 
 int /*<<< orphan*/  VSR_REF_CLOCK_CRTL ; 
 int mvs_read_port_vsr_data (struct mvs_info*,int) ; 
 int /*<<< orphan*/  mvs_write_port_vsr_addr (struct mvs_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_write_port_vsr_data (struct mvs_info*,int,int) ; 

__attribute__((used)) static void set_phy_ffe_tuning(struct mvs_info *mvi, int phy_id,
			       struct ffe_control ffe)
{
	u32 tmp;

	/* Don't run this if A0/B0 */
	if ((mvi->pdev->revision == VANIR_A0_REV)
		|| (mvi->pdev->revision == VANIR_B0_REV))
		return;

	/* FFE Resistor and Capacitor */
	/* R10Ch DFE Resolution Control/Squelch and FFE Setting
	 *
	 * FFE_FORCE            [7]
	 * FFE_RES_SEL          [6:4]
	 * FFE_CAP_SEL          [3:0]
	 */
	mvs_write_port_vsr_addr(mvi, phy_id, VSR_PHY_FFE_CONTROL);
	tmp = mvs_read_port_vsr_data(mvi, phy_id);
	tmp &= ~0xFF;

	/* Read from HBA_Info_Page */
	tmp |= ((0x1 << 7) |
		(ffe.ffe_rss_sel << 4) |
		(ffe.ffe_cap_sel << 0));

	mvs_write_port_vsr_data(mvi, phy_id, tmp);

	/* R064h PHY Mode Register 1
	 *
	 * DFE_DIS		18
	 */
	mvs_write_port_vsr_addr(mvi, phy_id, VSR_REF_CLOCK_CRTL);
	tmp = mvs_read_port_vsr_data(mvi, phy_id);
	tmp &= ~0x40001;
	/* Hard coding */
	/* No defines in HBA_Info_Page */
	tmp |= (0 << 18);
	mvs_write_port_vsr_data(mvi, phy_id, tmp);

	/* R110h DFE F0-F1 Coefficient Control/DFE Update Control
	 *
	 * DFE_UPDATE_EN        [11:6]
	 * DFE_FX_FORCE         [5:0]
	 */
	mvs_write_port_vsr_addr(mvi, phy_id, VSR_PHY_DFE_UPDATE_CRTL);
	tmp = mvs_read_port_vsr_data(mvi, phy_id);
	tmp &= ~0xFFF;
	/* Hard coding */
	/* No defines in HBA_Info_Page */
	tmp |= ((0x3F << 6) | (0x0 << 0));
	mvs_write_port_vsr_data(mvi, phy_id, tmp);

	/* R1A0h Interface and Digital Reference Clock Control/Reserved_50h
	 *
	 * FFE_TRAIN_EN         3
	 */
	mvs_write_port_vsr_addr(mvi, phy_id, VSR_REF_CLOCK_CRTL);
	tmp = mvs_read_port_vsr_data(mvi, phy_id);
	tmp &= ~0x8;
	/* Hard coding */
	/* No defines in HBA_Info_Page */
	tmp |= (0 << 3);
	mvs_write_port_vsr_data(mvi, phy_id, tmp);
}