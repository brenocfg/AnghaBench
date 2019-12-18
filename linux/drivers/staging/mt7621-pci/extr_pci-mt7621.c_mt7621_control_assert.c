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
struct mt7621_pcie_port {int /*<<< orphan*/  pcie_rst; } ;

/* Variables and functions */
 int CHIP_REV_MT7621_E2 ; 
 int /*<<< orphan*/  MT7621_CHIP_REV_ID ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int rt_sysc_r32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mt7621_control_assert(struct mt7621_pcie_port *port)
{
	u32 chip_rev_id = rt_sysc_r32(MT7621_CHIP_REV_ID);

	if ((chip_rev_id & 0xFFFF) == CHIP_REV_MT7621_E2)
		reset_control_assert(port->pcie_rst);
	else
		reset_control_deassert(port->pcie_rst);
}