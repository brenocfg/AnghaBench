#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t nleft; size_t nbits; int word; } ;
typedef  TYPE_1__ adpcm_state ;

/* Variables and functions */
 int* bitmask ; 

__attribute__((used)) static int
isdn_audio_get_bits(adpcm_state *s, unsigned char **in, int *len)
{
	while (s->nleft < s->nbits) {
		int d = *((*in)++);
		(*len)--;
		s->word = (s->word << 8) | d;
		s->nleft += 8;
	}
	s->nleft -= s->nbits;
	return (s->word >> s->nleft) & bitmask[s->nbits];
}