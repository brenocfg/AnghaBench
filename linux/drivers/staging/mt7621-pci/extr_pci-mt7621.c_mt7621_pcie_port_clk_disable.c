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
struct mt7621_pcie_port {int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_PORT_CLK_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RALINK_CLKCFG1 ; 
 int /*<<< orphan*/  rt_sysc_m32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mt7621_pcie_port_clk_disable(struct mt7621_pcie_port *port)
{
	rt_sysc_m32(PCIE_PORT_CLK_EN(port->slot), 0, RALINK_CLKCFG1);
}