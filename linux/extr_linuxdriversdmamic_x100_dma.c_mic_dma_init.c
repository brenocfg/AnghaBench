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
struct mic_dma_device {int start_ch; struct mic_dma_chan* mic_ch; } ;
struct mic_dma_chan {int ch_num; int owner; int /*<<< orphan*/  issue_lock; int /*<<< orphan*/  prep_lock; int /*<<< orphan*/  cleanup_lock; } ;
typedef  enum mic_dma_chan_owner { ____Placeholder_mic_dma_chan_owner } mic_dma_chan_owner ;

/* Variables and functions */
 int MIC_DMA_NUM_CHAN ; 
 int /*<<< orphan*/  mic_dma_free_irq (struct mic_dma_chan*) ; 
 int mic_dma_setup_irq (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mic_dma_init(struct mic_dma_device *mic_dma_dev,
			enum mic_dma_chan_owner owner)
{
	int i, first_chan = mic_dma_dev->start_ch;
	struct mic_dma_chan *ch;
	int ret;

	for (i = first_chan; i < first_chan + MIC_DMA_NUM_CHAN; i++) {
		ch = &mic_dma_dev->mic_ch[i];
		ch->ch_num = i;
		ch->owner = owner;
		spin_lock_init(&ch->cleanup_lock);
		spin_lock_init(&ch->prep_lock);
		spin_lock_init(&ch->issue_lock);
		ret = mic_dma_setup_irq(ch);
		if (ret)
			goto error;
	}
	return 0;
error:
	for (i = i - 1; i >= first_chan; i--)
		mic_dma_free_irq(ch);
	return ret;
}