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
struct snd_cobalt_card {int /*<<< orphan*/  hwptr_done_capture; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 struct snd_cobalt_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static
snd_pcm_uframes_t snd_cobalt_pcm_pointer(struct snd_pcm_substream *substream)
{
	snd_pcm_uframes_t hwptr_done;
	struct snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);

	hwptr_done = cobsc->hwptr_done_capture;

	return hwptr_done;
}