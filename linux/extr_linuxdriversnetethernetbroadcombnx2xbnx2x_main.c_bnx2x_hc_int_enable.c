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
struct TYPE_2__ {scalar_t__ pmf; } ;
struct bnx2x {int flags; TYPE_1__ port; } ;

/* Variables and functions */
 int BP_PORT (struct bnx2x*) ; 
 int BP_VN (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int HC_CONFIG_0_REG_ATTN_BIT_EN_0 ; 
 int HC_CONFIG_0_REG_INT_LINE_EN_0 ; 
 int HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0 ; 
 int HC_CONFIG_0_REG_SINGLE_ISR_EN_0 ; 
 int HC_REG_CONFIG_0 ; 
 int HC_REG_CONFIG_1 ; 
 int HC_REG_INT_MASK ; 
 int HC_REG_LEADING_EDGE_0 ; 
 int HC_REG_TRAILING_EDGE_0 ; 
 scalar_t__ IS_MF (struct bnx2x*) ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
 int USING_MSIX_FLAG ; 
 int USING_MSI_FLAG ; 
 int USING_SINGLE_MSIX_FLAG ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  mmiowb () ; 

__attribute__((used)) static void bnx2x_hc_int_enable(struct bnx2x *bp)
{
	int port = BP_PORT(bp);
	u32 addr = port ? HC_REG_CONFIG_1 : HC_REG_CONFIG_0;
	u32 val = REG_RD(bp, addr);
	bool msix = (bp->flags & USING_MSIX_FLAG) ? true : false;
	bool single_msix = (bp->flags & USING_SINGLE_MSIX_FLAG) ? true : false;
	bool msi = (bp->flags & USING_MSI_FLAG) ? true : false;

	if (msix) {
		val &= ~(HC_CONFIG_0_REG_SINGLE_ISR_EN_0 |
			 HC_CONFIG_0_REG_INT_LINE_EN_0);
		val |= (HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0 |
			HC_CONFIG_0_REG_ATTN_BIT_EN_0);
		if (single_msix)
			val |= HC_CONFIG_0_REG_SINGLE_ISR_EN_0;
	} else if (msi) {
		val &= ~HC_CONFIG_0_REG_INT_LINE_EN_0;
		val |= (HC_CONFIG_0_REG_SINGLE_ISR_EN_0 |
			HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0 |
			HC_CONFIG_0_REG_ATTN_BIT_EN_0);
	} else {
		val |= (HC_CONFIG_0_REG_SINGLE_ISR_EN_0 |
			HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0 |
			HC_CONFIG_0_REG_INT_LINE_EN_0 |
			HC_CONFIG_0_REG_ATTN_BIT_EN_0);

		if (!CHIP_IS_E1(bp)) {
			DP(NETIF_MSG_IFUP,
			   "write %x to HC %d (addr 0x%x)\n", val, port, addr);

			REG_WR(bp, addr, val);

			val &= ~HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0;
		}
	}

	if (CHIP_IS_E1(bp))
		REG_WR(bp, HC_REG_INT_MASK + port*4, 0x1FFFF);

	DP(NETIF_MSG_IFUP,
	   "write %x to HC %d (addr 0x%x) mode %s\n", val, port, addr,
	   (msix ? "MSI-X" : (msi ? "MSI" : "INTx")));

	REG_WR(bp, addr, val);
	/*
	 * Ensure that HC_CONFIG is written before leading/trailing edge config
	 */
	mmiowb();
	barrier();

	if (!CHIP_IS_E1(bp)) {
		/* init leading/trailing edge */
		if (IS_MF(bp)) {
			val = (0xee0f | (1 << (BP_VN(bp) + 4)));
			if (bp->port.pmf)
				/* enable nig and gpio3 attention */
				val |= 0x1100;
		} else
			val = 0xffff;

		REG_WR(bp, HC_REG_TRAILING_EDGE_0 + port*8, val);
		REG_WR(bp, HC_REG_LEADING_EDGE_0 + port*8, val);
	}

	/* Make sure that interrupts are indeed enabled from here on */
	mmiowb();
}