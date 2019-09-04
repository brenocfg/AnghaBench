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
struct xgene_ahci_context {scalar_t__ csr_mux; } ;

/* Variables and functions */
 int CFG_SATA_ENET_SELECT_MASK ; 
 scalar_t__ SATA_ENET_CONFIG_REG ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int xgene_ahci_mux_select(struct xgene_ahci_context *ctx)
{
	u32 val;

	/* Check for optional MUX resource */
	if (!ctx->csr_mux)
		return 0;

	val = readl(ctx->csr_mux + SATA_ENET_CONFIG_REG);
	val &= ~CFG_SATA_ENET_SELECT_MASK;
	writel(val, ctx->csr_mux + SATA_ENET_CONFIG_REG);
	val = readl(ctx->csr_mux + SATA_ENET_CONFIG_REG);
	return val & CFG_SATA_ENET_SELECT_MASK ? -1 : 0;
}