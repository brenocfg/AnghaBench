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
struct TYPE_2__ {int /*<<< orphan*/  slock; int /*<<< orphan*/  hwptr_done_capture; } ;
struct cx231xx {TYPE_1__ adev; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 struct cx231xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_cx231xx_capture_pointer(struct snd_pcm_substream
						     *substream)
{
	struct cx231xx *dev;
	unsigned long flags;
	snd_pcm_uframes_t hwptr_done;

	dev = snd_pcm_substream_chip(substream);

	spin_lock_irqsave(&dev->adev.slock, flags);
	hwptr_done = dev->adev.hwptr_done_capture;
	spin_unlock_irqrestore(&dev->adev.slock, flags);

	return hwptr_done;
}