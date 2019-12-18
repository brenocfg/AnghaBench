#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tw686x_dev {scalar_t__ dma_mode; TYPE_2__* pci_dev; } ;
struct tw686x_audio_channel {size_t ch; TYPE_1__* dma_descs; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  size; void* virt; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ADMA_B_ADDR ; 
 int /*<<< orphan*/ * ADMA_P_ADDR ; 
 int /*<<< orphan*/  AUDIO_DMA_SIZE_MAX ; 
 int ENOMEM ; 
 scalar_t__ TW686X_DMA_MODE_MEMCPY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t,char*) ; 
 void* pci_alloc_consistent (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_write (struct tw686x_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tw686x_audio_dma_alloc(struct tw686x_dev *dev,
				  struct tw686x_audio_channel *ac)
{
	int pb;

	/*
	 * In the memcpy DMA mode we allocate a consistent buffer
	 * and use it for the DMA capture. Otherwise, DMA
	 * acts on the ALSA buffers as received in pcm_prepare.
	 */
	if (dev->dma_mode != TW686X_DMA_MODE_MEMCPY)
		return 0;

	for (pb = 0; pb < 2; pb++) {
		u32 reg = pb ? ADMA_B_ADDR[ac->ch] : ADMA_P_ADDR[ac->ch];
		void *virt;

		virt = pci_alloc_consistent(dev->pci_dev, AUDIO_DMA_SIZE_MAX,
					    &ac->dma_descs[pb].phys);
		if (!virt) {
			dev_err(&dev->pci_dev->dev,
				"dma%d: unable to allocate audio DMA %s-buffer\n",
				ac->ch, pb ? "B" : "P");
			return -ENOMEM;
		}
		ac->dma_descs[pb].virt = virt;
		ac->dma_descs[pb].size = AUDIO_DMA_SIZE_MAX;
		reg_write(dev, reg, ac->dma_descs[pb].phys);
	}
	return 0;
}