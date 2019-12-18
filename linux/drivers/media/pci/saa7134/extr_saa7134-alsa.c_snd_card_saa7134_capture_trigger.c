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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {TYPE_1__* private_data; } ;
struct saa7134_dev {int /*<<< orphan*/  slock; } ;
struct TYPE_2__ {struct saa7134_dev* dev; } ;
typedef  TYPE_1__ snd_card_saa7134_pcm_t ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_PCM_TRIGGER_START ; 
 int SNDRV_PCM_TRIGGER_STOP ; 
 int /*<<< orphan*/  saa7134_dma_start (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_dma_stop (struct saa7134_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_card_saa7134_capture_trigger(struct snd_pcm_substream * substream,
					  int cmd)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	snd_card_saa7134_pcm_t *pcm = runtime->private_data;
	struct saa7134_dev *dev=pcm->dev;
	int err = 0;

	spin_lock(&dev->slock);
	if (cmd == SNDRV_PCM_TRIGGER_START) {
		/* start dma */
		saa7134_dma_start(dev);
	} else if (cmd == SNDRV_PCM_TRIGGER_STOP) {
		/* stop dma */
		saa7134_dma_stop(dev);
	} else {
		err = -EINVAL;
	}
	spin_unlock(&dev->slock);

	return err;
}