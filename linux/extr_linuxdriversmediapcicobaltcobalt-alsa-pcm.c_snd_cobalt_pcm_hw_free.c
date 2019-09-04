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
struct TYPE_2__ {int /*<<< orphan*/ * dma_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cobalt_pcm_hw_free(struct snd_pcm_substream *substream)
{
	if (substream->runtime->dma_area) {
		dprintk("freeing pcm capture region\n");
		vfree(substream->runtime->dma_area);
		substream->runtime->dma_area = NULL;
	}

	return 0;
}