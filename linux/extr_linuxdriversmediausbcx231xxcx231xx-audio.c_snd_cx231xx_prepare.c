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
struct TYPE_2__ {scalar_t__ capture_transfer_done; scalar_t__ hwptr_done_capture; } ;
struct cx231xx {TYPE_1__ adev; } ;

/* Variables and functions */
 struct cx231xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cx231xx_prepare(struct snd_pcm_substream *substream)
{
	struct cx231xx *dev = snd_pcm_substream_chip(substream);

	dev->adev.hwptr_done_capture = 0;
	dev->adev.capture_transfer_done = 0;

	return 0;
}