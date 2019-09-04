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
struct TYPE_2__ {int /*<<< orphan*/  wq_trigger; int /*<<< orphan*/  stream_started; } ;
struct em28xx {TYPE_1__ adev; scalar_t__ disconnected; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct em28xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_em28xx_capture_trigger(struct snd_pcm_substream *substream,
				      int cmd)
{
	struct em28xx *dev = snd_pcm_substream_chip(substream);
	int retval = 0;

	if (dev->disconnected)
		return -ENODEV;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE: /* fall through */
	case SNDRV_PCM_TRIGGER_RESUME: /* fall through */
	case SNDRV_PCM_TRIGGER_START:
		atomic_set(&dev->adev.stream_started, 1);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH: /* fall through */
	case SNDRV_PCM_TRIGGER_SUSPEND: /* fall through */
	case SNDRV_PCM_TRIGGER_STOP:
		atomic_set(&dev->adev.stream_started, 0);
		break;
	default:
		retval = -EINVAL;
	}
	schedule_work(&dev->adev.wq_trigger);
	return retval;
}