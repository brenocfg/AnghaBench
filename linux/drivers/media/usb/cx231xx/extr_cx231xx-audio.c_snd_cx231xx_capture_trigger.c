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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  slock; } ;
struct cx231xx {int state; int /*<<< orphan*/  wq_trigger; TYPE_1__ adev; int /*<<< orphan*/  stream_started; } ;

/* Variables and functions */
 int DEV_DISCONNECTED ; 
 int EINVAL ; 
 int ENODEV ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct cx231xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cx231xx_capture_trigger(struct snd_pcm_substream *substream,
				       int cmd)
{
	struct cx231xx *dev = snd_pcm_substream_chip(substream);
	int retval = 0;

	if (dev->state & DEV_DISCONNECTED)
		return -ENODEV;

	spin_lock(&dev->adev.slock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		atomic_set(&dev->stream_started, 1);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		atomic_set(&dev->stream_started, 0);
		break;
	default:
		retval = -EINVAL;
		break;
	}
	spin_unlock(&dev->adev.slock);

	schedule_work(&dev->wq_trigger);

	return retval;
}