#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct mmc_request {TYPE_3__* data; TYPE_1__* cmd; } ;
struct mmc_host {TYPE_4__* card; } ;
struct cvm_mmc_slot {int /*<<< orphan*/  bus_id; } ;
struct TYPE_8__ {int cmds; } ;
struct TYPE_10__ {TYPE_2__ scr; } ;
struct TYPE_9__ {int flags; int blocks; } ;
struct TYPE_7__ {int arg; } ;

/* Variables and functions */
 int FIELD_PREP (int,int) ; 
 int MIO_EMM_DMA_BLOCK_CNT ; 
 int MIO_EMM_DMA_CARD_ADDR ; 
 int MIO_EMM_DMA_MULTI ; 
 int MIO_EMM_DMA_RW ; 
 int MIO_EMM_DMA_SECTOR ; 
 int MIO_EMM_DMA_VAL ; 
 int MMC_DATA_WRITE ; 
 int SD_SCR_CMD23_SUPPORT ; 
 scalar_t__ mmc_card_is_blockaddr (TYPE_4__*) ; 
 scalar_t__ mmc_card_mmc (TYPE_4__*) ; 
 scalar_t__ mmc_card_sd (TYPE_4__*) ; 
 struct cvm_mmc_slot* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int,int) ; 
 int /*<<< orphan*/  set_bus_id (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 prepare_ext_dma(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct cvm_mmc_slot *slot = mmc_priv(mmc);
	u64 emm_dma;

	emm_dma = FIELD_PREP(MIO_EMM_DMA_VAL, 1) |
		  FIELD_PREP(MIO_EMM_DMA_SECTOR,
			     mmc_card_is_blockaddr(mmc->card) ? 1 : 0) |
		  FIELD_PREP(MIO_EMM_DMA_RW,
			     (mrq->data->flags & MMC_DATA_WRITE) ? 1 : 0) |
		  FIELD_PREP(MIO_EMM_DMA_BLOCK_CNT, mrq->data->blocks) |
		  FIELD_PREP(MIO_EMM_DMA_CARD_ADDR, mrq->cmd->arg);
	set_bus_id(&emm_dma, slot->bus_id);

	if (mmc_card_mmc(mmc->card) || (mmc_card_sd(mmc->card) &&
	    (mmc->card->scr.cmds & SD_SCR_CMD23_SUPPORT)))
		emm_dma |= FIELD_PREP(MIO_EMM_DMA_MULTI, 1);

	pr_debug("[%s] blocks: %u  multi: %d\n",
		(emm_dma & MIO_EMM_DMA_RW) ? "W" : "R",
		 mrq->data->blocks, (emm_dma & MIO_EMM_DMA_MULTI) ? 1 : 0);
	return emm_dma;
}