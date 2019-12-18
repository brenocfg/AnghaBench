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
struct sr_pcie_phy_core {int /*<<< orphan*/  cdru; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDRU_STRAP_DATA_LSW_OFFSET ; 
 scalar_t__ PCIE_PIPEMUX_CFG_OFFSET ; 
 int PCIE_PIPEMUX_MASK ; 
 int PCIE_PIPEMUX_SELECT_STRAP ; 
 int PCIE_PIPEMUX_SHIFT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u32 pipemux_strap_read(struct sr_pcie_phy_core *core)
{
	u32 pipemux;

	/*
	 * Read PIPEMUX configuration register to determine the pipemux setting
	 *
	 * In the case when the value indicates using HW strap, fall back to
	 * use HW strap
	 */
	pipemux = readl(core->base + PCIE_PIPEMUX_CFG_OFFSET);
	pipemux &= PCIE_PIPEMUX_MASK;
	if (pipemux == PCIE_PIPEMUX_SELECT_STRAP) {
		regmap_read(core->cdru, CDRU_STRAP_DATA_LSW_OFFSET, &pipemux);
		pipemux >>= PCIE_PIPEMUX_SHIFT;
		pipemux &= PCIE_PIPEMUX_MASK;
	}

	return pipemux;
}