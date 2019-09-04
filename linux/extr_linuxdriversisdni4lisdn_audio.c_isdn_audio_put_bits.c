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
struct TYPE_3__ {int word; int nleft; } ;
typedef  TYPE_1__ adpcm_state ;

/* Variables and functions */
 int* bitmask ; 

__attribute__((used)) static void
isdn_audio_put_bits(int data, int nbits, adpcm_state *s,
		    unsigned char **out, int *len)
{
	s->word = (s->word << nbits) | (data & bitmask[nbits]);
	s->nleft += nbits;
	while (s->nleft >= 8) {
		int d = (s->word >> (s->nleft - 8));
		*(out[0]++) = d & 255;
		(*len)++;
		s->nleft -= 8;
	}
}