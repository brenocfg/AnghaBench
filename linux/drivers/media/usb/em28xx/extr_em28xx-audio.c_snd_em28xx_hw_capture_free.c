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
struct snd_pcm_substream {int dummy; } ;
struct em28xx_audio {int /*<<< orphan*/  wq_trigger; int /*<<< orphan*/  stream_started; } ;
struct em28xx {struct em28xx_audio adev; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct em28xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_em28xx_hw_capture_free(struct snd_pcm_substream *substream)
{
	struct em28xx *dev = snd_pcm_substream_chip(substream);
	struct em28xx_audio *adev = &dev->adev;

	dprintk("Stop capture, if needed\n");

	if (atomic_read(&adev->stream_started) > 0) {
		atomic_set(&adev->stream_started, 0);
		schedule_work(&adev->wq_trigger);
	}

	return 0;
}