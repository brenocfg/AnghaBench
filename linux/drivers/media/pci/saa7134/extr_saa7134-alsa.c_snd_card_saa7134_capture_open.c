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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; int /*<<< orphan*/  private_free; TYPE_4__* private_data; } ;
struct TYPE_8__ {int input; int /*<<< orphan*/  lock; scalar_t__ read_offset; scalar_t__ read_count; } ;
struct saa7134_dev {scalar_t__ ctl_mute; TYPE_2__ dmasound; TYPE_1__* input; } ;
struct TYPE_9__ {int mute_was_on; struct saa7134_dev* dev; } ;
typedef  TYPE_3__ snd_card_saa7134_t ;
struct TYPE_10__ {struct snd_pcm_substream* substream; int /*<<< orphan*/  lock; struct saa7134_dev* dev; } ;
typedef  TYPE_4__ snd_card_saa7134_pcm_t ;
struct TYPE_7__ {int amux; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 TYPE_4__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  saa7134_tvaudio_setmute (struct saa7134_dev*) ; 
 int /*<<< orphan*/  snd_card_saa7134_capture ; 
 int /*<<< orphan*/  snd_card_saa7134_runtime_free ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_card_saa7134_capture_open(struct snd_pcm_substream * substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	snd_card_saa7134_pcm_t *pcm;
	snd_card_saa7134_t *saa7134 = snd_pcm_substream_chip(substream);
	struct saa7134_dev *dev;
	int amux, err;

	if (!saa7134) {
		pr_err("BUG: saa7134 can't find device struct. Can't proceed with open\n");
		return -ENODEV;
	}
	dev = saa7134->dev;
	mutex_lock(&dev->dmasound.lock);

	dev->dmasound.read_count  = 0;
	dev->dmasound.read_offset = 0;

	amux = dev->input->amux;
	if ((amux < 1) || (amux > 3))
		amux = 1;
	dev->dmasound.input  =  amux - 1;

	mutex_unlock(&dev->dmasound.lock);

	pcm = kzalloc(sizeof(*pcm), GFP_KERNEL);
	if (pcm == NULL)
		return -ENOMEM;

	pcm->dev=saa7134->dev;

	spin_lock_init(&pcm->lock);

	pcm->substream = substream;
	runtime->private_data = pcm;
	runtime->private_free = snd_card_saa7134_runtime_free;
	runtime->hw = snd_card_saa7134_capture;

	if (dev->ctl_mute != 0) {
		saa7134->mute_was_on = 1;
		dev->ctl_mute = 0;
		saa7134_tvaudio_setmute(dev);
	}

	err = snd_pcm_hw_constraint_integer(runtime,
						SNDRV_PCM_HW_PARAM_PERIODS);
	if (err < 0)
		return err;

	err = snd_pcm_hw_constraint_step(runtime, 0,
						SNDRV_PCM_HW_PARAM_PERIODS, 2);
	if (err < 0)
		return err;

	return 0;
}