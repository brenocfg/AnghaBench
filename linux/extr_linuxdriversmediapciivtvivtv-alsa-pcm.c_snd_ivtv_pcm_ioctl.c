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
struct snd_ivtv_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ivtv_lock (struct snd_ivtv_card*) ; 
 int /*<<< orphan*/  snd_ivtv_unlock (struct snd_ivtv_card*) ; 
 int snd_pcm_lib_ioctl (struct snd_pcm_substream*,unsigned int,void*) ; 
 struct snd_ivtv_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ivtv_pcm_ioctl(struct snd_pcm_substream *substream,
		     unsigned int cmd, void *arg)
{
	struct snd_ivtv_card *itvsc = snd_pcm_substream_chip(substream);
	int ret;

	snd_ivtv_lock(itvsc);
	ret = snd_pcm_lib_ioctl(substream, cmd, arg);
	snd_ivtv_unlock(itvsc);
	return ret;
}