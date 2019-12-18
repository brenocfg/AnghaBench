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
struct snd_pcm_substream {int number; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; int /*<<< orphan*/  private_free; struct bcm2835_alsa_stream* private_data; } ;
struct bcm2835_chip {int opened; int /*<<< orphan*/  audio_mutex; struct bcm2835_alsa_stream** alsa_stream; scalar_t__ spdif_status; int /*<<< orphan*/  dev; } ;
struct bcm2835_alsa_stream {int idx; struct snd_pcm_substream* substream; struct bcm2835_chip* chip; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_SUBSTREAMS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_TIME ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int bcm2835_audio_open (struct bcm2835_alsa_stream*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  kfree (struct bcm2835_alsa_stream*) ; 
 struct bcm2835_alsa_stream* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_bcm2835_playback_free ; 
 int /*<<< orphan*/  snd_bcm2835_playback_hw ; 
 int /*<<< orphan*/  snd_bcm2835_playback_spdif_hw ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bcm2835_chip* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_bcm2835_playback_open_generic(
	struct snd_pcm_substream *substream, int spdif)
{
	struct bcm2835_chip *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct bcm2835_alsa_stream *alsa_stream;
	int idx;
	int err;

	mutex_lock(&chip->audio_mutex);
	idx = substream->number;

	if (spdif && chip->opened) {
		err = -EBUSY;
		goto out;
	} else if (!spdif && (chip->opened & (1 << idx))) {
		err = -EBUSY;
		goto out;
	}
	if (idx >= MAX_SUBSTREAMS) {
		dev_err(chip->dev,
			"substream(%d) device doesn't exist max(%d) substreams allowed\n",
			idx, MAX_SUBSTREAMS);
		err = -ENODEV;
		goto out;
	}

	alsa_stream = kzalloc(sizeof(*alsa_stream), GFP_KERNEL);
	if (!alsa_stream) {
		err = -ENOMEM;
		goto out;
	}

	/* Initialise alsa_stream */
	alsa_stream->chip = chip;
	alsa_stream->substream = substream;
	alsa_stream->idx = idx;

	err = bcm2835_audio_open(alsa_stream);
	if (err) {
		kfree(alsa_stream);
		goto out;
	}
	runtime->private_data = alsa_stream;
	runtime->private_free = snd_bcm2835_playback_free;
	if (spdif) {
		runtime->hw = snd_bcm2835_playback_spdif_hw;
	} else {
		/* clear spdif status, as we are not in spdif mode */
		chip->spdif_status = 0;
		runtime->hw = snd_bcm2835_playback_hw;
	}
	/* minimum 16 bytes alignment (for vchiq bulk transfers) */
	snd_pcm_hw_constraint_step(runtime,
				   0,
				   SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
				   16);

	/* position update is in 10ms order */
	snd_pcm_hw_constraint_minmax(runtime,
				     SNDRV_PCM_HW_PARAM_PERIOD_TIME,
				     10 * 1000, UINT_MAX);

	chip->alsa_stream[idx] = alsa_stream;

	chip->opened |= (1 << idx);

out:
	mutex_unlock(&chip->audio_mutex);

	return err;
}