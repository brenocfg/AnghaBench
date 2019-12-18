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
struct xilinx_pcie_port {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XILINX_PCIE_REG_RPEFR ; 
 int /*<<< orphan*/  XILINX_PCIE_RPEFR_ALL_MASK ; 
 unsigned long XILINX_PCIE_RPEFR_ERR_VALID ; 
 unsigned long XILINX_PCIE_RPEFR_REQ_ID ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long) ; 
 unsigned long pcie_read (struct xilinx_pcie_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_write (struct xilinx_pcie_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xilinx_pcie_clear_err_interrupts(struct xilinx_pcie_port *port)
{
	struct device *dev = port->dev;
	unsigned long val = pcie_read(port, XILINX_PCIE_REG_RPEFR);

	if (val & XILINX_PCIE_RPEFR_ERR_VALID) {
		dev_dbg(dev, "Requester ID %lu\n",
			val & XILINX_PCIE_RPEFR_REQ_ID);
		pcie_write(port, XILINX_PCIE_RPEFR_ALL_MASK,
			   XILINX_PCIE_REG_RPEFR);
	}
}