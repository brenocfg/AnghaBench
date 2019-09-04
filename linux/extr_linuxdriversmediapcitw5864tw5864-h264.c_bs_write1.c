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
typedef  int u32 ;
struct bs {int* ptr; int* buf_end; int bits_left; } ;

/* Variables and functions */

__attribute__((used)) static void bs_write1(struct bs *s, u32 bit)
{
	if (s->ptr < s->buf_end) {
		*s->ptr <<= 1;
		*s->ptr |= bit;
		s->bits_left--;
		if (s->bits_left == 0) {
			s->ptr++;
			s->bits_left = 8;
		}
	}
}