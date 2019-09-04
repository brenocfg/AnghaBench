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
struct snd_pcm_runtime {struct cx231xx* private_data; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {struct snd_pcm_substream* capture_pcm_substream; int /*<<< orphan*/  users; } ;
struct cx231xx {int state; TYPE_1__ adev; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; scalar_t__ USE_ISO; } ;

/* Variables and functions */
 int /*<<< orphan*/  Audio ; 
 int DEV_DISCONNECTED ; 
 int ENODEV ; 
 int /*<<< orphan*/  INDEX_AUDIO ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int cx231xx_capture_start (struct cx231xx*,int,int /*<<< orphan*/ ) ; 
 int cx231xx_set_alt_setting (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_cx231xx_hw_capture ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct cx231xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cx231xx_capture_open(struct snd_pcm_substream *substream)
{
	struct cx231xx *dev = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int ret = 0;

	dev_dbg(dev->dev,
		"opening device and trying to acquire exclusive lock\n");

	if (dev->state & DEV_DISCONNECTED) {
		dev_err(dev->dev,
			"Can't open. the device was removed.\n");
		return -ENODEV;
	}

	/* set alternate setting for audio interface */
	/* 1 - 48000 samples per sec */
	mutex_lock(&dev->lock);
	if (dev->USE_ISO)
		ret = cx231xx_set_alt_setting(dev, INDEX_AUDIO, 1);
	else
		ret = cx231xx_set_alt_setting(dev, INDEX_AUDIO, 0);
	mutex_unlock(&dev->lock);
	if (ret < 0) {
		dev_err(dev->dev,
			"failed to set alternate setting !\n");

		return ret;
	}

	runtime->hw = snd_cx231xx_hw_capture;

	mutex_lock(&dev->lock);
	/* inform hardware to start streaming */
	ret = cx231xx_capture_start(dev, 1, Audio);

	dev->adev.users++;
	mutex_unlock(&dev->lock);

	snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS);
	dev->adev.capture_pcm_substream = substream;
	runtime->private_data = dev;

	return 0;
}