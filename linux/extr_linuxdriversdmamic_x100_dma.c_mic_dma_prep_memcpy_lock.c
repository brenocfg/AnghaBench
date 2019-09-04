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
struct mic_dma_chan {int /*<<< orphan*/  prep_lock; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 struct dma_async_tx_descriptor* allocate_tx (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* mic_dma_ch_to_device (struct mic_dma_chan*) ; 
 int mic_dma_do_dma (struct mic_dma_chan*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct mic_dma_chan* to_mic_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
mic_dma_prep_memcpy_lock(struct dma_chan *ch, dma_addr_t dma_dest,
			 dma_addr_t dma_src, size_t len, unsigned long flags)
{
	struct mic_dma_chan *mic_ch = to_mic_dma_chan(ch);
	struct device *dev = mic_dma_ch_to_device(mic_ch);
	int result;

	if (!len && !flags)
		return NULL;

	spin_lock(&mic_ch->prep_lock);
	result = mic_dma_do_dma(mic_ch, flags, dma_src, dma_dest, len);
	if (result >= 0)
		return allocate_tx(mic_ch);
	dev_err(dev, "Error enqueueing dma, error=%d\n", result);
	spin_unlock(&mic_ch->prep_lock);
	return NULL;
}