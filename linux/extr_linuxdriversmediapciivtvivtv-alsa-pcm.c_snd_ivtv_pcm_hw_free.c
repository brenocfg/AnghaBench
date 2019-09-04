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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_ivtv_card {int /*<<< orphan*/  slock; } ;
struct TYPE_2__ {unsigned char* dma_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 struct snd_ivtv_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vfree (unsigned char*) ; 

__attribute__((used)) static int snd_ivtv_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_ivtv_card *itvsc = snd_pcm_substream_chip(substream);
	unsigned long flags;
	unsigned char *dma_area = NULL;

	spin_lock_irqsave(&itvsc->slock, flags);
	if (substream->runtime->dma_area) {
		dprintk("freeing pcm capture region\n");
		dma_area = substream->runtime->dma_area;
		substream->runtime->dma_area = NULL;
	}
	spin_unlock_irqrestore(&itvsc->slock, flags);
	vfree(dma_area);

	return 0;
}