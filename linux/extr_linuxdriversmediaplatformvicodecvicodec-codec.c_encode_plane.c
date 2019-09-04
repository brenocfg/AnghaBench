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
typedef  int u32 ;
struct cframe {int /*<<< orphan*/  coeffs; int /*<<< orphan*/  de_fwht; int /*<<< orphan*/  de_coeffs; } ;
typedef  int s16 ;
typedef  int __be16 ;

/* Variables and functions */
 int DUPS_MASK ; 
 int FRAME_PCODED ; 
 int FRAME_UNENCODED ; 
 int IBLOCK ; 
 int PBLOCK ; 
 int PFRAME_BIT ; 
 int /*<<< orphan*/  add_deltas (int /*<<< orphan*/ ,int*,int) ; 
 int decide_blocktype (int*,int*,int*,int,unsigned int) ; 
 int /*<<< orphan*/  fill_decoder_block (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fwht (int*,int /*<<< orphan*/ ,int,unsigned int,int) ; 
 int /*<<< orphan*/  fwht16 (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int htons (int) ; 
 int /*<<< orphan*/  ifwht (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int ntohs (int) ; 
 int /*<<< orphan*/  quantize_inter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quantize_intra (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int rlc (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static u32 encode_plane(u8 *input, u8 *refp, __be16 **rlco, __be16 *rlco_max,
			struct cframe *cf, u32 height, u32 width,
			unsigned int input_step,
			bool is_intra, bool next_is_intra)
{
	u8 *input_start = input;
	__be16 *rlco_start = *rlco;
	s16 deltablock[64];
	__be16 pframe_bit = htons(PFRAME_BIT);
	u32 encoding = 0;
	unsigned int last_size = 0;
	unsigned int i, j;

	for (j = 0; j < height / 8; j++) {
		for (i = 0; i < width / 8; i++) {
			/* intra code, first frame is always intra coded. */
			int blocktype = IBLOCK;
			unsigned int size;

			if (!is_intra)
				blocktype = decide_blocktype(input, refp,
					deltablock, width, input_step);
			if (is_intra || blocktype == IBLOCK) {
				fwht(input, cf->coeffs, width, input_step, 1);
				quantize_intra(cf->coeffs, cf->de_coeffs);
				blocktype = IBLOCK;
			} else {
				/* inter code */
				encoding |= FRAME_PCODED;
				fwht16(deltablock, cf->coeffs, 8, 0);
				quantize_inter(cf->coeffs, cf->de_coeffs);
			}
			if (!next_is_intra) {
				ifwht(cf->de_coeffs, cf->de_fwht, blocktype);

				if (blocktype == PBLOCK)
					add_deltas(cf->de_fwht, refp, 8);
				fill_decoder_block(refp, cf->de_fwht, 8);
			}

			input += 8 * input_step;
			refp += 8 * 8;

			if (encoding & FRAME_UNENCODED)
				continue;

			size = rlc(cf->coeffs, *rlco, blocktype);
			if (last_size == size &&
			    !memcmp(*rlco + 1, *rlco - size + 1, 2 * size - 2)) {
				__be16 *last_rlco = *rlco - size;
				s16 hdr = ntohs(*last_rlco);

				if (!((*last_rlco ^ **rlco) & pframe_bit) &&
				    (hdr & DUPS_MASK) < DUPS_MASK)
					*last_rlco = htons(hdr + 2);
				else
					*rlco += size;
			} else {
				*rlco += size;
			}
			if (*rlco >= rlco_max)
				encoding |= FRAME_UNENCODED;
			last_size = size;
		}
		input += width * 7 * input_step;
	}
	if (encoding & FRAME_UNENCODED) {
		u8 *out = (u8 *)rlco_start;

		input = input_start;
		/*
		 * The compressed stream should never contain the magic
		 * header, so when we copy the YUV data we replace 0xff
		 * by 0xfe. Since YUV is limited range such values
		 * shouldn't appear anyway.
		 */
		for (i = 0; i < height * width; i++, input += input_step)
			*out++ = (*input == 0xff) ? 0xfe : *input;
		*rlco = (__be16 *)out;
	}
	return encoding;
}