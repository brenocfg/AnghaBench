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
struct smi_settings {int pack_data; int dma_passthrough_enable; int dma_enable; void* dma_panic_write_thresh; void* dma_panic_read_thresh; void* dma_write_thresh; void* dma_read_thresh; void* write_strobe_time; void* write_pace_time; void* write_hold_time; void* write_setup_time; void* read_strobe_time; void* read_pace_time; void* read_hold_time; void* read_setup_time; void* data_width; } ;
struct bcm2835_smi_instance {int /*<<< orphan*/  transaction_lock; struct smi_settings settings; } ;

/* Variables and functions */
 void* GET_BIT_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMICS ; 
 int SMICS_PXLDAT ; 
 int /*<<< orphan*/  SMIDC ; 
 int SMIDC_DMAEN ; 
 int SMIDC_DMAP ; 
 int /*<<< orphan*/  SMIDC_PANICR ; 
 int /*<<< orphan*/  SMIDC_PANICW ; 
 int /*<<< orphan*/  SMIDC_REQR ; 
 int /*<<< orphan*/  SMIDC_REQW ; 
 int /*<<< orphan*/  SMIDSR0 ; 
 int /*<<< orphan*/  SMIDSR_RHOLD ; 
 int /*<<< orphan*/  SMIDSR_RPACE ; 
 int /*<<< orphan*/  SMIDSR_RSETUP ; 
 int /*<<< orphan*/  SMIDSR_RSTROBE ; 
 int /*<<< orphan*/  SMIDSR_RWIDTH ; 
 int /*<<< orphan*/  SMIDSW0 ; 
 int /*<<< orphan*/  SMIDSW_WHOLD ; 
 int /*<<< orphan*/  SMIDSW_WPACE ; 
 int /*<<< orphan*/  SMIDSW_WSETUP ; 
 int /*<<< orphan*/  SMIDSW_WSTROBE ; 
 int read_smi_reg (struct bcm2835_smi_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct smi_settings *bcm2835_smi_get_settings_from_regs
	(struct bcm2835_smi_instance *inst)
{
	struct smi_settings *settings = &inst->settings;
	int smidsr, smidsw, smidc;

	spin_lock(&inst->transaction_lock);

	smidsr = read_smi_reg(inst, SMIDSR0);
	smidsw = read_smi_reg(inst, SMIDSW0);
	smidc = read_smi_reg(inst, SMIDC);

	settings->pack_data = (read_smi_reg(inst, SMICS) & SMICS_PXLDAT) ?
	    true : false;

	settings->data_width = GET_BIT_FIELD(smidsr, SMIDSR_RWIDTH);
	settings->read_setup_time = GET_BIT_FIELD(smidsr, SMIDSR_RSETUP);
	settings->read_hold_time = GET_BIT_FIELD(smidsr, SMIDSR_RHOLD);
	settings->read_pace_time = GET_BIT_FIELD(smidsr, SMIDSR_RPACE);
	settings->read_strobe_time = GET_BIT_FIELD(smidsr, SMIDSR_RSTROBE);

	settings->write_setup_time = GET_BIT_FIELD(smidsw, SMIDSW_WSETUP);
	settings->write_hold_time = GET_BIT_FIELD(smidsw, SMIDSW_WHOLD);
	settings->write_pace_time = GET_BIT_FIELD(smidsw, SMIDSW_WPACE);
	settings->write_strobe_time = GET_BIT_FIELD(smidsw, SMIDSW_WSTROBE);

	settings->dma_read_thresh = GET_BIT_FIELD(smidc, SMIDC_REQR);
	settings->dma_write_thresh = GET_BIT_FIELD(smidc, SMIDC_REQW);
	settings->dma_panic_read_thresh = GET_BIT_FIELD(smidc, SMIDC_PANICR);
	settings->dma_panic_write_thresh = GET_BIT_FIELD(smidc, SMIDC_PANICW);
	settings->dma_passthrough_enable = (smidc & SMIDC_DMAP) ? true : false;
	settings->dma_enable = (smidc & SMIDC_DMAEN) ? true : false;

	spin_unlock(&inst->transaction_lock);

	return settings;
}