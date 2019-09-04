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
struct smi_settings {scalar_t__ data_width; scalar_t__ read_setup_time; scalar_t__ read_hold_time; scalar_t__ read_pace_time; scalar_t__ read_strobe_time; scalar_t__ write_setup_time; scalar_t__ write_hold_time; scalar_t__ write_pace_time; scalar_t__ write_strobe_time; scalar_t__ dma_read_thresh; scalar_t__ dma_write_thresh; scalar_t__ dma_panic_read_thresh; scalar_t__ dma_panic_write_thresh; scalar_t__ dma_enable; scalar_t__ dma_passthrough_enable; scalar_t__ pack_data; } ;
struct bcm2835_smi_instance {int /*<<< orphan*/  transaction_lock; struct smi_settings settings; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_BIT_FIELD (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SMICS ; 
 int SMICS_PXLDAT ; 
 int /*<<< orphan*/  SMIDC ; 
 int /*<<< orphan*/  SMIDCS ; 
 int SMIDC_DMAEN ; 
 int SMIDC_DMAP ; 
 int /*<<< orphan*/  SMIDC_PANICR ; 
 int /*<<< orphan*/  SMIDC_PANICW ; 
 int /*<<< orphan*/  SMIDC_REQR ; 
 int /*<<< orphan*/  SMIDC_REQW ; 
 int /*<<< orphan*/  SMIDSR0 ; 
 int SMIDSR_RDREQ ; 
 int /*<<< orphan*/  SMIDSR_RHOLD ; 
 int /*<<< orphan*/  SMIDSR_RPACE ; 
 int /*<<< orphan*/  SMIDSR_RSETUP ; 
 int /*<<< orphan*/  SMIDSR_RSTROBE ; 
 int /*<<< orphan*/  SMIDSR_RWIDTH ; 
 int /*<<< orphan*/  SMIDSW0 ; 
 int SMIDSW_WDREQ ; 
 int /*<<< orphan*/  SMIDSW_WHOLD ; 
 int /*<<< orphan*/  SMIDSW_WPACE ; 
 int /*<<< orphan*/  SMIDSW_WSETUP ; 
 int /*<<< orphan*/  SMIDSW_WSTROBE ; 
 int SMIDSW_WSWAP ; 
 int /*<<< orphan*/  SMIDSW_WWIDTH ; 
 scalar_t__ SMI_WIDTH_8BIT ; 
 int read_smi_reg (struct bcm2835_smi_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_smi_reg (struct bcm2835_smi_instance*,int,int /*<<< orphan*/ ) ; 

void bcm2835_smi_set_regs_from_settings(struct bcm2835_smi_instance *inst)
{
	struct smi_settings *settings = &inst->settings;
	int smidsr_temp = 0, smidsw_temp = 0, smics_temp,
	    smidcs_temp, smidc_temp = 0;

	spin_lock(&inst->transaction_lock);

	/* temporarily disable the peripheral: */
	smics_temp = read_smi_reg(inst, SMICS);
	write_smi_reg(inst, 0, SMICS);
	smidcs_temp = read_smi_reg(inst, SMIDCS);
	write_smi_reg(inst, 0, SMIDCS);

	if (settings->pack_data)
		smics_temp |= SMICS_PXLDAT;
	else
		smics_temp &= ~SMICS_PXLDAT;

	SET_BIT_FIELD(smidsr_temp, SMIDSR_RWIDTH, settings->data_width);
	SET_BIT_FIELD(smidsr_temp, SMIDSR_RSETUP, settings->read_setup_time);
	SET_BIT_FIELD(smidsr_temp, SMIDSR_RHOLD, settings->read_hold_time);
	SET_BIT_FIELD(smidsr_temp, SMIDSR_RPACE, settings->read_pace_time);
	SET_BIT_FIELD(smidsr_temp, SMIDSR_RSTROBE, settings->read_strobe_time);
	write_smi_reg(inst, smidsr_temp, SMIDSR0);

	SET_BIT_FIELD(smidsw_temp, SMIDSW_WWIDTH, settings->data_width);
	if (settings->data_width == SMI_WIDTH_8BIT)
		smidsw_temp |= SMIDSW_WSWAP;
	else
		smidsw_temp &= ~SMIDSW_WSWAP;
	SET_BIT_FIELD(smidsw_temp, SMIDSW_WSETUP, settings->write_setup_time);
	SET_BIT_FIELD(smidsw_temp, SMIDSW_WHOLD, settings->write_hold_time);
	SET_BIT_FIELD(smidsw_temp, SMIDSW_WPACE, settings->write_pace_time);
	SET_BIT_FIELD(smidsw_temp, SMIDSW_WSTROBE,
			settings->write_strobe_time);
	write_smi_reg(inst, smidsw_temp, SMIDSW0);

	SET_BIT_FIELD(smidc_temp, SMIDC_REQR, settings->dma_read_thresh);
	SET_BIT_FIELD(smidc_temp, SMIDC_REQW, settings->dma_write_thresh);
	SET_BIT_FIELD(smidc_temp, SMIDC_PANICR,
		      settings->dma_panic_read_thresh);
	SET_BIT_FIELD(smidc_temp, SMIDC_PANICW,
		      settings->dma_panic_write_thresh);
	if (settings->dma_passthrough_enable) {
		smidc_temp |= SMIDC_DMAP;
		smidsr_temp |= SMIDSR_RDREQ;
		write_smi_reg(inst, smidsr_temp, SMIDSR0);
		smidsw_temp |= SMIDSW_WDREQ;
		write_smi_reg(inst, smidsw_temp, SMIDSW0);
	} else
		smidc_temp &= ~SMIDC_DMAP;
	if (settings->dma_enable)
		smidc_temp |= SMIDC_DMAEN;
	else
		smidc_temp &= ~SMIDC_DMAEN;

	write_smi_reg(inst, smidc_temp, SMIDC);

	/* re-enable (if was previously enabled) */
	write_smi_reg(inst, smics_temp, SMICS);
	write_smi_reg(inst, smidcs_temp, SMIDCS);

	spin_unlock(&inst->transaction_lock);
}