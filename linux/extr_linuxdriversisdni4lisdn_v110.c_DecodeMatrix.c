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
struct TYPE_3__ {int introducer; int dbit; unsigned char b; } ;
typedef  TYPE_1__ isdn_v110_stream ;

/* Variables and functions */

__attribute__((used)) static int
DecodeMatrix(isdn_v110_stream *v, unsigned char *m, int len, unsigned char *buf)
{
	int line = 0;
	int buflen = 0;
	int mbit = 64;
	int introducer = v->introducer;
	int dbit = v->dbit;
	unsigned char b = v->b;

	while (line < len) {    /* Are we done with all lines of the matrix? */
		if ((line % 10) == 0) {	/* the 0. line of the matrix is always 0 ! */
			if (m[line] != 0x00) {	/* not 0 ? -> error! */
#ifdef ISDN_V110_DEBUG
				printk(KERN_DEBUG "isdn_v110: DecodeMatrix, V110 Bad Header\n");
				/* returning now is not the right thing, though :-( */
#endif
			}
			line++; /* next line of matrix */
			continue;
		} else if ((line % 10) == 5) {	/* in line 5 there's only e-bits ! */
			if ((m[line] & 0x70) != 0x30) {	/* 011 has to be at the beginning! */
#ifdef ISDN_V110_DEBUG
				printk(KERN_DEBUG "isdn_v110: DecodeMatrix, V110 Bad 5th line\n");
				/* returning now is not the right thing, though :-( */
#endif
			}
			line++; /* next line */
			continue;
		} else if (!introducer) {	/* every byte starts with 10 (stopbit, startbit) */
			introducer = (m[line] & mbit) ? 0 : 1;	/* current bit of the matrix */
		next_byte:
			if (mbit > 2) {	/* was it the last bit in this line ? */
				mbit >>= 1;	/* no -> take next */
				continue;
			}       /* otherwise start with leftmost bit in the next line */
			mbit = 64;
			line++;
			continue;
		} else {        /* otherwise we need to set a data bit */
			if (m[line] & mbit)	/* was that bit set in the matrix ? */
				b |= dbit;	/* yes -> set it in the data byte */
			else
				b &= dbit - 1;	/* no -> clear it in the data byte */
			if (dbit < 128)	/* is that data byte done ? */
				dbit <<= 1;	/* no, got the next bit */
			else {  /* data byte is done */
				buf[buflen++] = b;	/* copy byte into the output buffer */
				introducer = b = 0;	/* init of the intro sequence and of the data byte */
				dbit = 1;	/* next we look for the 0th bit */
			}
			goto next_byte;	/* look for next bit in the matrix */
		}
	}
	v->introducer = introducer;
	v->dbit = dbit;
	v->b = b;
	return buflen;          /* return number of bytes in the output buffer */
}