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
struct usbtv {int /*<<< orphan*/  snd_buffer_pos; } ;
struct snd_pcm_substream {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 struct usbtv* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_usbtv_pointer(struct snd_pcm_substream *substream)
{
	struct usbtv *chip = snd_pcm_substream_chip(substream);

	return chip->snd_buffer_pos;
}