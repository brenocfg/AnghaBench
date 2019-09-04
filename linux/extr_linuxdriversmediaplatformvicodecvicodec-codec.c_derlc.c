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
typedef  int s16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 
 int* zigzag ; 

__attribute__((used)) static s16 derlc(const __be16 **rlc_in, s16 *dwht_out)
{
	/* header */
	const __be16 *input = *rlc_in;
	s16 ret = ntohs(*input++);
	int dec_count = 0;
	s16 block[8 * 8 + 16];
	s16 *wp = block;
	int i;

	/*
	 * Now de-compress, it expands one byte to up to 15 bytes
	 * (or fills the remainder of the 64 bytes with zeroes if it
	 * is the last byte to expand).
	 *
	 * So block has to be 8 * 8 + 16 bytes, the '+ 16' is to
	 * allow for overflow if the incoming data was malformed.
	 */
	while (dec_count < 8 * 8) {
		s16 in = ntohs(*input++);
		int length = in & 0xf;
		int coeff = in >> 4;

		/* fill remainder with zeros */
		if (length == 15) {
			for (i = 0; i < 64 - dec_count; i++)
				*wp++ = 0;
			break;
		}

		for (i = 0; i < length; i++)
			*wp++ = 0;
		*wp++ = coeff;
		dec_count += length + 1;
	}

	wp = block;

	for (i = 0; i < 64; i++) {
		int pos = zigzag[i];
		int y = pos / 8;
		int x = pos % 8;

		dwht_out[x + y * 8] = *wp++;
	}
	*rlc_in = input;
	return ret;
}