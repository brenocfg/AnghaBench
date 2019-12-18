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
typedef  size_t u8 ;
struct sk_buff {int len; size_t* data; } ;

/* Variables and functions */
 size_t** dsp_audio_volume_change ; 

void
dsp_change_volume(struct sk_buff *skb, int volume)
{
	u8 *volume_change;
	int i, ii;
	u8 *p;
	int shift;

	if (volume == 0)
		return;

	/* get correct conversion table */
	if (volume < 0) {
		shift = volume + 8;
		if (shift < 0)
			shift = 0;
	} else {
		shift = volume + 7;
		if (shift > 15)
			shift = 15;
	}
	volume_change = dsp_audio_volume_change[shift];
	i = 0;
	ii = skb->len;
	p = skb->data;
	/* change volume */
	while (i < ii) {
		*p = volume_change[*p];
		p++;
		i++;
	}
}