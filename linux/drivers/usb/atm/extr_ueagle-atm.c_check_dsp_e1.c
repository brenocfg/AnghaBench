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
typedef  int u8 ;
typedef  unsigned int u32 ;
typedef  unsigned int u16 ;

/* Variables and functions */
 int FW_GET_BYTE (int const*) ; 
 unsigned int get_unaligned_le16 (int const*) ; 
 unsigned int get_unaligned_le32 (int const*) ; 

__attribute__((used)) static int check_dsp_e1(const u8 *dsp, unsigned int len)
{
	u8 pagecount, blockcount;
	u16 blocksize;
	u32 pageoffset;
	unsigned int i, j, p, pp;

	pagecount = FW_GET_BYTE(dsp);
	p = 1;

	/* enough space for page offsets? */
	if (p + 4 * pagecount > len)
		return 1;

	for (i = 0; i < pagecount; i++) {

		pageoffset = get_unaligned_le32(dsp + p);
		p += 4;

		if (pageoffset == 0)
			continue;

		/* enough space for blockcount? */
		if (pageoffset >= len)
			return 1;

		pp = pageoffset;
		blockcount = FW_GET_BYTE(dsp + pp);
		pp += 1;

		for (j = 0; j < blockcount; j++) {

			/* enough space for block header? */
			if (pp + 4 > len)
				return 1;

			pp += 2;	/* skip blockaddr */
			blocksize = get_unaligned_le16(dsp + pp);
			pp += 2;

			/* enough space for block data? */
			if (pp + blocksize > len)
				return 1;

			pp += blocksize;
		}
	}

	return 0;
}