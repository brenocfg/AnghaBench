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
struct snd_cx18_card {scalar_t__ capture_transfer_done; scalar_t__ hwptr_done_capture; } ;

/* Variables and functions */
 struct snd_cx18_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cx18_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_cx18_card *cxsc = snd_pcm_substream_chip(substream);

	cxsc->hwptr_done_capture = 0;
	cxsc->capture_transfer_done = 0;

	return 0;
}