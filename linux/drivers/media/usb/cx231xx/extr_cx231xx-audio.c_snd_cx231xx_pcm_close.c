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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_4__ {scalar_t__ users; int shutdown; } ;
struct cx231xx {int /*<<< orphan*/  wq_trigger; int /*<<< orphan*/  stream_started; int /*<<< orphan*/  dev; TYPE_2__ adev; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dma_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  Audio ; 
 int /*<<< orphan*/  INDEX_AUDIO ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cx231xx_capture_start (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cx231xx_set_alt_setting (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct cx231xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cx231xx_pcm_close(struct snd_pcm_substream *substream)
{
	int ret;
	struct cx231xx *dev = snd_pcm_substream_chip(substream);

	dev_dbg(dev->dev, "closing device\n");

	/* inform hardware to stop streaming */
	mutex_lock(&dev->lock);
	ret = cx231xx_capture_start(dev, 0, Audio);

	/* set alternate setting for audio interface */
	/* 1 - 48000 samples per sec */
	ret = cx231xx_set_alt_setting(dev, INDEX_AUDIO, 0);
	if (ret < 0) {
		dev_err(dev->dev,
			"failed to set alternate setting !\n");

		mutex_unlock(&dev->lock);
		return ret;
	}

	dev->adev.users--;
	if (substream->runtime->dma_area) {
		dev_dbg(dev->dev, "freeing\n");
		vfree(substream->runtime->dma_area);
		substream->runtime->dma_area = NULL;
	}
	mutex_unlock(&dev->lock);

	if (dev->adev.users == 0 && dev->adev.shutdown == 1) {
		dev_dbg(dev->dev, "audio users: %d\n", dev->adev.users);
		dev_dbg(dev->dev, "disabling audio stream!\n");
		dev->adev.shutdown = 0;
		dev_dbg(dev->dev, "released lock\n");
		if (atomic_read(&dev->stream_started) > 0) {
			atomic_set(&dev->stream_started, 0);
			schedule_work(&dev->wq_trigger);
		}
	}
	return 0;
}