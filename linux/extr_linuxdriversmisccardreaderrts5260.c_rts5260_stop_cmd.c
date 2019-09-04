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
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RBCTL ; 
 int RB_FLUSH ; 
 int RTS5260_ADMA3_RST ; 
 int RTS5260_DMA_RST ; 
 int /*<<< orphan*/  RTS5260_DMA_RST_CTL_0 ; 
 int /*<<< orphan*/  RTSX_HCBCTLR ; 
 int /*<<< orphan*/  RTSX_HDBCTLR ; 
 int /*<<< orphan*/  STOP_CMD ; 
 int /*<<< orphan*/  STOP_DMA ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_pci_writel (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rts5260_stop_cmd(struct rtsx_pcr *pcr)
{
	rtsx_pci_writel(pcr, RTSX_HCBCTLR, STOP_CMD);
	rtsx_pci_writel(pcr, RTSX_HDBCTLR, STOP_DMA);
	rtsx_pci_write_register(pcr, RTS5260_DMA_RST_CTL_0,
				RTS5260_DMA_RST | RTS5260_ADMA3_RST,
				RTS5260_DMA_RST | RTS5260_ADMA3_RST);
	rtsx_pci_write_register(pcr, RBCTL, RB_FLUSH, RB_FLUSH);
}