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
struct usbtv {scalar_t__ snd_period_pos; scalar_t__ snd_buffer_pos; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 struct usbtv* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_usbtv_prepare(struct snd_pcm_substream *substream)
{
	struct usbtv *chip = snd_pcm_substream_chip(substream);

	chip->snd_buffer_pos = 0;
	chip->snd_period_pos = 0;

	return 0;
}