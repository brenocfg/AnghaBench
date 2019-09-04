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
struct xgene_edac_mc_ctx {scalar_t__ mcu_csr; int /*<<< orphan*/  edac; } ;
struct mem_ctl_info {int /*<<< orphan*/  ctl_name; struct xgene_edac_mc_ctx* pvt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 int /*<<< orphan*/  HW_EVENT_ERR_UNCORRECTED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ MCUEBLRR0 ; 
 scalar_t__ MCUERCRR0 ; 
 scalar_t__ MCUESRR0 ; 
 scalar_t__ MCUGESR ; 
 scalar_t__ MCUSBECNT0 ; 
 unsigned int MCU_CORR_ERR_MASK ; 
 unsigned int MCU_CTL_ERR_MASK ; 
 int /*<<< orphan*/  MCU_EBLRR_ERRBANK_RD (int) ; 
 int /*<<< orphan*/  MCU_ERCRR_ERRCOL_RD (int) ; 
 int /*<<< orphan*/  MCU_ERCRR_ERRROW_RD (int) ; 
 int MCU_ESRR_BACKUCERR_MASK ; 
 int MCU_ESRR_CERR_MASK ; 
 int MCU_ESRR_DEMANDUCERR_MASK ; 
 int MCU_GESR_ADDRMULTIMATCH_ERR_MASK ; 
 int MCU_GESR_ADDRNOMATCH_ERR_MASK ; 
 int MCU_MAX_RANK ; 
 int MCU_RANK_STRIDE ; 
 int /*<<< orphan*/  MCU_SBECNT_COUNT (int) ; 
 unsigned int MCU_UNCORR_ERR_MASK ; 
 int /*<<< orphan*/  PCPHPERRINTSTS ; 
 int /*<<< orphan*/  PCPLPERRINTSTS ; 
 int /*<<< orphan*/  edac_mc_chipset_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  xgene_edac_pcp_rd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void xgene_edac_mc_check(struct mem_ctl_info *mci)
{
	struct xgene_edac_mc_ctx *ctx = mci->pvt_info;
	unsigned int pcp_hp_stat;
	unsigned int pcp_lp_stat;
	u32 reg;
	u32 rank;
	u32 bank;
	u32 count;
	u32 col_row;

	xgene_edac_pcp_rd(ctx->edac, PCPHPERRINTSTS, &pcp_hp_stat);
	xgene_edac_pcp_rd(ctx->edac, PCPLPERRINTSTS, &pcp_lp_stat);
	if (!((MCU_UNCORR_ERR_MASK & pcp_hp_stat) ||
	      (MCU_CTL_ERR_MASK & pcp_hp_stat) ||
	      (MCU_CORR_ERR_MASK & pcp_lp_stat)))
		return;

	for (rank = 0; rank < MCU_MAX_RANK; rank++) {
		reg = readl(ctx->mcu_csr + MCUESRR0 + rank * MCU_RANK_STRIDE);

		/* Detect uncorrectable memory error */
		if (reg & (MCU_ESRR_DEMANDUCERR_MASK |
			   MCU_ESRR_BACKUCERR_MASK)) {
			/* Detected uncorrectable memory error */
			edac_mc_chipset_printk(mci, KERN_ERR, "X-Gene",
				"MCU uncorrectable error at rank %d\n", rank);

			edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci,
				1, 0, 0, 0, 0, 0, -1, mci->ctl_name, "");
		}

		/* Detect correctable memory error */
		if (reg & MCU_ESRR_CERR_MASK) {
			bank = readl(ctx->mcu_csr + MCUEBLRR0 +
				     rank * MCU_RANK_STRIDE);
			col_row = readl(ctx->mcu_csr + MCUERCRR0 +
					rank * MCU_RANK_STRIDE);
			count = readl(ctx->mcu_csr + MCUSBECNT0 +
				      rank * MCU_RANK_STRIDE);
			edac_mc_chipset_printk(mci, KERN_WARNING, "X-Gene",
				"MCU correctable error at rank %d bank %d column %d row %d count %d\n",
				rank, MCU_EBLRR_ERRBANK_RD(bank),
				MCU_ERCRR_ERRCOL_RD(col_row),
				MCU_ERCRR_ERRROW_RD(col_row),
				MCU_SBECNT_COUNT(count));

			edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci,
				1, 0, 0, 0, 0, 0, -1, mci->ctl_name, "");
		}

		/* Clear all error registers */
		writel(0x0, ctx->mcu_csr + MCUEBLRR0 + rank * MCU_RANK_STRIDE);
		writel(0x0, ctx->mcu_csr + MCUERCRR0 + rank * MCU_RANK_STRIDE);
		writel(0x0, ctx->mcu_csr + MCUSBECNT0 +
		       rank * MCU_RANK_STRIDE);
		writel(reg, ctx->mcu_csr + MCUESRR0 + rank * MCU_RANK_STRIDE);
	}

	/* Detect memory controller error */
	reg = readl(ctx->mcu_csr + MCUGESR);
	if (reg) {
		if (reg & MCU_GESR_ADDRNOMATCH_ERR_MASK)
			edac_mc_chipset_printk(mci, KERN_WARNING, "X-Gene",
				"MCU address miss-match error\n");
		if (reg & MCU_GESR_ADDRMULTIMATCH_ERR_MASK)
			edac_mc_chipset_printk(mci, KERN_WARNING, "X-Gene",
				"MCU address multi-match error\n");

		writel(reg, ctx->mcu_csr + MCUGESR);
	}
}