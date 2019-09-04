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
typedef  void* __be16 ;

/* Variables and functions */
 int ALL_ZEROS ; 
 int PBLOCK ; 
 int PFRAME_BIT ; 
 void* htons (int) ; 
 size_t* zigzag ; 

__attribute__((used)) static int rlc(const s16 *in, __be16 *output, int blocktype)
{
	s16 block[8 * 8];
	s16 *wp = block;
	int i = 0;
	int x, y;
	int ret = 0;

	/* read in block from framebuffer */
	int lastzero_run = 0;
	int to_encode;

	for (y = 0; y < 8; y++) {
		for (x = 0; x < 8; x++) {
			*wp = in[x + y * 8];
			wp++;
		}
	}

	/* keep track of amount of trailing zeros */
	for (i = 63; i >= 0 && !block[zigzag[i]]; i--)
		lastzero_run++;

	*output++ = (blocktype == PBLOCK ? htons(PFRAME_BIT) : 0);
	ret++;

	to_encode = 8 * 8 - (lastzero_run > 14 ? lastzero_run : 0);

	i = 0;
	while (i < to_encode) {
		int cnt = 0;
		int tmp;

		/* count leading zeros */
		while ((tmp = block[zigzag[i]]) == 0 && cnt < 14) {
			cnt++;
			i++;
			if (i == to_encode) {
				cnt--;
				break;
			}
		}
		/* 4 bits for run, 12 for coefficient (quantization by 4) */
		*output++ = htons((cnt | tmp << 4));
		i++;
		ret++;
	}
	if (lastzero_run > 14) {
		*output = htons(ALL_ZEROS | 0);
		ret++;
	}

	return ret;
}