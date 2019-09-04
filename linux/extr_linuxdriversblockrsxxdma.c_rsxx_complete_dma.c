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
struct TYPE_2__ {int /*<<< orphan*/  dma_cancelled; int /*<<< orphan*/  dma_hw_fault; int /*<<< orphan*/  dma_sw_err; } ;
struct rsxx_dma_ctrl {int /*<<< orphan*/  card; TYPE_1__ stats; } ;
struct rsxx_dma {int /*<<< orphan*/  cb_data; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 unsigned int DMA_CANCELLED ; 
 unsigned int DMA_HW_FAULT ; 
 unsigned int DMA_SW_ERR ; 
 int /*<<< orphan*/  rsxx_free_dma (struct rsxx_dma_ctrl*,struct rsxx_dma*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rsxx_complete_dma(struct rsxx_dma_ctrl *ctrl,
				  struct rsxx_dma *dma,
				  unsigned int status)
{
	if (status & DMA_SW_ERR)
		ctrl->stats.dma_sw_err++;
	if (status & DMA_HW_FAULT)
		ctrl->stats.dma_hw_fault++;
	if (status & DMA_CANCELLED)
		ctrl->stats.dma_cancelled++;

	if (dma->cb)
		dma->cb(ctrl->card, dma->cb_data, status ? 1 : 0);

	rsxx_free_dma(ctrl, dma);
}