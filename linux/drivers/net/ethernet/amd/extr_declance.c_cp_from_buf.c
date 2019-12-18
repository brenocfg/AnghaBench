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

/* Variables and functions */
 int const PMAD_LANCE ; 
 int const PMAX_LANCE ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 

__attribute__((used)) static void cp_from_buf(const int type, void *to, const void *from, int len)
{
	unsigned short *tp;
	const unsigned short *fp;
	unsigned short clen;
	unsigned char *rtp;
	const unsigned char *rfp;

	if (type == PMAD_LANCE) {
		memcpy(to, from, len);
	} else if (type == PMAX_LANCE) {
		clen = len >> 1;
		tp = to;
		fp = from;
		while (clen--) {
			*tp++ = *fp++;
			fp++;
		}

		clen = len & 1;

		rtp = (unsigned char *)tp;
		rfp = (const unsigned char *)fp;

		while (clen--) {
			*rtp++ = *rfp++;
		}
	} else {

		/*
		 * copy 16 Byte chunks
		 */
		clen = len >> 4;
		tp = to;
		fp = from;
		while (clen--) {
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			fp += 8;
		}

		/*
		 * do the rest, if any.
		 */
		clen = len & 15;
		rtp = (unsigned char *)tp;
		rfp = (const unsigned char *)fp;
		while (clen--) {
			*rtp++ = *rfp++;
		}


	}

}