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
struct mem_ctl_info {int /*<<< orphan*/  ctl_name; struct altr_sdram_mc_data* pvt_info; } ;
struct altr_sdram_prv_data {int ecc_stat_ue_mask; int ecc_stat_ce_mask; int /*<<< orphan*/  ecc_irq_clr_mask; int /*<<< orphan*/  ecc_irq_clr_offset; scalar_t__ ecc_cecnt_offset; scalar_t__ ecc_uecnt_offset; scalar_t__ ecc_saddr_offset; scalar_t__ ecc_daddr_offset; scalar_t__ ecc_stat_offset; } ;
struct altr_sdram_mc_data {int /*<<< orphan*/  mc_vbase; struct altr_sdram_prv_data* data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  panic (char*,int,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t altr_sdram_mc_err_handler(int irq, void *dev_id)
{
	struct mem_ctl_info *mci = dev_id;
	struct altr_sdram_mc_data *drvdata = mci->pvt_info;
	const struct altr_sdram_prv_data *priv = drvdata->data;
	u32 status, err_count = 1, err_addr;

	regmap_read(drvdata->mc_vbase, priv->ecc_stat_offset, &status);

	if (status & priv->ecc_stat_ue_mask) {
		regmap_read(drvdata->mc_vbase, priv->ecc_daddr_offset,
			    &err_addr);
		if (priv->ecc_uecnt_offset)
			regmap_read(drvdata->mc_vbase, priv->ecc_uecnt_offset,
				    &err_count);
		panic("\nEDAC: [%d Uncorrectable errors @ 0x%08X]\n",
		      err_count, err_addr);
	}
	if (status & priv->ecc_stat_ce_mask) {
		regmap_read(drvdata->mc_vbase, priv->ecc_saddr_offset,
			    &err_addr);
		if (priv->ecc_uecnt_offset)
			regmap_read(drvdata->mc_vbase,  priv->ecc_cecnt_offset,
				    &err_count);
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, err_count,
				     err_addr >> PAGE_SHIFT,
				     err_addr & ~PAGE_MASK, 0,
				     0, 0, -1, mci->ctl_name, "");
		/* Clear IRQ to resume */
		regmap_write(drvdata->mc_vbase,	priv->ecc_irq_clr_offset,
			     priv->ecc_irq_clr_mask);

		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}