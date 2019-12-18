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
struct xilinx_pcie_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XILINX_PCIE_REG_PSCR ; 
 int XILINX_PCIE_REG_PSCR_LNKUP ; 
 int pcie_read (struct xilinx_pcie_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool xilinx_pcie_link_up(struct xilinx_pcie_port *port)
{
	return (pcie_read(port, XILINX_PCIE_REG_PSCR) &
		XILINX_PCIE_REG_PSCR_LNKUP) ? 1 : 0;
}