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
struct seq_file {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_CLK_CTRL ; 
 int /*<<< orphan*/  DSI_CLK_TIMING ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_CFG1 ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_CFG2 ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_IRQ_ENABLE ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_IRQ_STATUS ; 
 int /*<<< orphan*/  DSI_CTRL ; 
 int /*<<< orphan*/  DSI_DSIPHY_CFG0 ; 
 int /*<<< orphan*/  DSI_DSIPHY_CFG1 ; 
 int /*<<< orphan*/  DSI_DSIPHY_CFG2 ; 
 int /*<<< orphan*/  DSI_DSIPHY_CFG5 ; 
 int /*<<< orphan*/  DSI_IRQENABLE ; 
 int /*<<< orphan*/  DSI_IRQSTATUS ; 
 int /*<<< orphan*/  DSI_PLL_CONFIGURATION1 ; 
 int /*<<< orphan*/  DSI_PLL_CONFIGURATION2 ; 
 int /*<<< orphan*/  DSI_PLL_CONTROL ; 
 int /*<<< orphan*/  DSI_PLL_GO ; 
 int /*<<< orphan*/  DSI_PLL_STATUS ; 
 int /*<<< orphan*/  DSI_REVISION ; 
 int /*<<< orphan*/  DSI_RX_FIFO_VC_FULLNESS ; 
 int /*<<< orphan*/  DSI_RX_FIFO_VC_SIZE ; 
 int /*<<< orphan*/  DSI_STOPCLK_TIMING ; 
 int /*<<< orphan*/  DSI_SYSCONFIG ; 
 int /*<<< orphan*/  DSI_SYSSTATUS ; 
 int /*<<< orphan*/  DSI_TIMING1 ; 
 int /*<<< orphan*/  DSI_TIMING2 ; 
 int /*<<< orphan*/  DSI_TX_FIFO_VC_EMPTINESS ; 
 int /*<<< orphan*/  DSI_TX_FIFO_VC_SIZE ; 
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int /*<<< orphan*/  DSI_VC_IRQENABLE (int) ; 
 int /*<<< orphan*/  DSI_VC_IRQSTATUS (int) ; 
 int /*<<< orphan*/  DSI_VC_LONG_PACKET_HEADER (int) ; 
 int /*<<< orphan*/  DSI_VC_LONG_PACKET_PAYLOAD (int) ; 
 int /*<<< orphan*/  DSI_VC_SHORT_PACKET_HEADER (int) ; 
 int /*<<< orphan*/  DSI_VC_TE (int) ; 
 int /*<<< orphan*/  DSI_VM_TIMING1 ; 
 int /*<<< orphan*/  DSI_VM_TIMING2 ; 
 int /*<<< orphan*/  DSI_VM_TIMING3 ; 
 int /*<<< orphan*/  DSI_VM_TIMING4 ; 
 int /*<<< orphan*/  DSI_VM_TIMING5 ; 
 int /*<<< orphan*/  DSI_VM_TIMING6 ; 
 int /*<<< orphan*/  DSI_VM_TIMING7 ; 
 int /*<<< orphan*/  DUMPREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_disable_scp_clk (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_enable_scp_clk (struct platform_device*) ; 
 scalar_t__ dsi_runtime_get (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_runtime_put (struct platform_device*) ; 

__attribute__((used)) static void dsi_dump_dsidev_regs(struct platform_device *dsidev,
		struct seq_file *s)
{
#define DUMPREG(r) seq_printf(s, "%-35s %08x\n", #r, dsi_read_reg(dsidev, r))

	if (dsi_runtime_get(dsidev))
		return;
	dsi_enable_scp_clk(dsidev);

	DUMPREG(DSI_REVISION);
	DUMPREG(DSI_SYSCONFIG);
	DUMPREG(DSI_SYSSTATUS);
	DUMPREG(DSI_IRQSTATUS);
	DUMPREG(DSI_IRQENABLE);
	DUMPREG(DSI_CTRL);
	DUMPREG(DSI_COMPLEXIO_CFG1);
	DUMPREG(DSI_COMPLEXIO_IRQ_STATUS);
	DUMPREG(DSI_COMPLEXIO_IRQ_ENABLE);
	DUMPREG(DSI_CLK_CTRL);
	DUMPREG(DSI_TIMING1);
	DUMPREG(DSI_TIMING2);
	DUMPREG(DSI_VM_TIMING1);
	DUMPREG(DSI_VM_TIMING2);
	DUMPREG(DSI_VM_TIMING3);
	DUMPREG(DSI_CLK_TIMING);
	DUMPREG(DSI_TX_FIFO_VC_SIZE);
	DUMPREG(DSI_RX_FIFO_VC_SIZE);
	DUMPREG(DSI_COMPLEXIO_CFG2);
	DUMPREG(DSI_RX_FIFO_VC_FULLNESS);
	DUMPREG(DSI_VM_TIMING4);
	DUMPREG(DSI_TX_FIFO_VC_EMPTINESS);
	DUMPREG(DSI_VM_TIMING5);
	DUMPREG(DSI_VM_TIMING6);
	DUMPREG(DSI_VM_TIMING7);
	DUMPREG(DSI_STOPCLK_TIMING);

	DUMPREG(DSI_VC_CTRL(0));
	DUMPREG(DSI_VC_TE(0));
	DUMPREG(DSI_VC_LONG_PACKET_HEADER(0));
	DUMPREG(DSI_VC_LONG_PACKET_PAYLOAD(0));
	DUMPREG(DSI_VC_SHORT_PACKET_HEADER(0));
	DUMPREG(DSI_VC_IRQSTATUS(0));
	DUMPREG(DSI_VC_IRQENABLE(0));

	DUMPREG(DSI_VC_CTRL(1));
	DUMPREG(DSI_VC_TE(1));
	DUMPREG(DSI_VC_LONG_PACKET_HEADER(1));
	DUMPREG(DSI_VC_LONG_PACKET_PAYLOAD(1));
	DUMPREG(DSI_VC_SHORT_PACKET_HEADER(1));
	DUMPREG(DSI_VC_IRQSTATUS(1));
	DUMPREG(DSI_VC_IRQENABLE(1));

	DUMPREG(DSI_VC_CTRL(2));
	DUMPREG(DSI_VC_TE(2));
	DUMPREG(DSI_VC_LONG_PACKET_HEADER(2));
	DUMPREG(DSI_VC_LONG_PACKET_PAYLOAD(2));
	DUMPREG(DSI_VC_SHORT_PACKET_HEADER(2));
	DUMPREG(DSI_VC_IRQSTATUS(2));
	DUMPREG(DSI_VC_IRQENABLE(2));

	DUMPREG(DSI_VC_CTRL(3));
	DUMPREG(DSI_VC_TE(3));
	DUMPREG(DSI_VC_LONG_PACKET_HEADER(3));
	DUMPREG(DSI_VC_LONG_PACKET_PAYLOAD(3));
	DUMPREG(DSI_VC_SHORT_PACKET_HEADER(3));
	DUMPREG(DSI_VC_IRQSTATUS(3));
	DUMPREG(DSI_VC_IRQENABLE(3));

	DUMPREG(DSI_DSIPHY_CFG0);
	DUMPREG(DSI_DSIPHY_CFG1);
	DUMPREG(DSI_DSIPHY_CFG2);
	DUMPREG(DSI_DSIPHY_CFG5);

	DUMPREG(DSI_PLL_CONTROL);
	DUMPREG(DSI_PLL_STATUS);
	DUMPREG(DSI_PLL_GO);
	DUMPREG(DSI_PLL_CONFIGURATION1);
	DUMPREG(DSI_PLL_CONFIGURATION2);

	dsi_disable_scp_clk(dsidev);
	dsi_runtime_put(dsidev);
#undef DUMPREG
}