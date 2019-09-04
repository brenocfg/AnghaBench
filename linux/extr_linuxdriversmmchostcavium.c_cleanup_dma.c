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
typedef  int u64 ;
struct cvm_mmc_host {scalar_t__ base; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MIO_EMM_DMA (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  MIO_EMM_DMA_DAT_NULL ; 
 int /*<<< orphan*/  MIO_EMM_DMA_VAL ; 
 int /*<<< orphan*/  get_bus_id (int) ; 
 int readq (scalar_t__) ; 
 int /*<<< orphan*/  set_bus_id (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

__attribute__((used)) static void cleanup_dma(struct cvm_mmc_host *host, u64 rsp_sts)
{
	u64 emm_dma;

	emm_dma = readq(host->base + MIO_EMM_DMA(host));
	emm_dma |= FIELD_PREP(MIO_EMM_DMA_VAL, 1) |
		   FIELD_PREP(MIO_EMM_DMA_DAT_NULL, 1);
	set_bus_id(&emm_dma, get_bus_id(rsp_sts));
	writeq(emm_dma, host->base + MIO_EMM_DMA(host));
}