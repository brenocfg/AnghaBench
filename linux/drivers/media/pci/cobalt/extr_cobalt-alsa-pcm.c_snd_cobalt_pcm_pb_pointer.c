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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_cobalt_card {size_t pb_pos; } ;
typedef  int snd_pcm_uframes_t ;
struct TYPE_2__ {int buffer_size; } ;

/* Variables and functions */
 int bytes_to_frames (TYPE_1__*,size_t) ; 
 struct snd_cobalt_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static
snd_pcm_uframes_t snd_cobalt_pcm_pb_pointer(struct snd_pcm_substream *substream)
{
	struct snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);
	size_t ptr;

	ptr = cobsc->pb_pos;

	return bytes_to_frames(substream->runtime, ptr) %
	       substream->runtime->buffer_size;
}