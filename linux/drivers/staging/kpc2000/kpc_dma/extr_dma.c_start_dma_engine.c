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
struct kpc_dma_device {int /*<<< orphan*/  desc_pool_first; int /*<<< orphan*/  desc_pool_last; int /*<<< orphan*/  desc_completed; int /*<<< orphan*/  desc_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearEngineCompletePtr (struct kpc_dma_device*) ; 
 int ENG_CTL_DMA_ENABLE ; 
 int ENG_CTL_IRQ_ENABLE ; 
 int /*<<< orphan*/  SetEngineNextPtr (struct kpc_dma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEngineSWPtr (struct kpc_dma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteEngineControl (struct kpc_dma_device*,int) ; 

void  start_dma_engine(struct kpc_dma_device *eng)
{
	eng->desc_next       = eng->desc_pool_first;
	eng->desc_completed  = eng->desc_pool_last;

	// Setup the engine pointer registers
	SetEngineNextPtr(eng, eng->desc_pool_first);
	SetEngineSWPtr(eng, eng->desc_pool_first);
	ClearEngineCompletePtr(eng);

	WriteEngineControl(eng, ENG_CTL_DMA_ENABLE | ENG_CTL_IRQ_ENABLE);
}