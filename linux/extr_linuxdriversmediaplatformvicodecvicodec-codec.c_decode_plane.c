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
struct cframe {int* de_fwht; int /*<<< orphan*/  coeffs; } ;
typedef  int s16 ;
typedef  int /*<<< orphan*/  copy ;
typedef  int __be16 ;

/* Variables and functions */
 int DUPS_MASK ; 
 int PFRAME_BIT ; 
 int /*<<< orphan*/  add_deltas (int*,int*,int) ; 
 int /*<<< orphan*/  dequantize_inter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dequantize_intra (int /*<<< orphan*/ ) ; 
 int derlc (int const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_decoder_block (int*,int*,int) ; 
 int /*<<< orphan*/  ifwht (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static void decode_plane(struct cframe *cf, const __be16 **rlco, u8 *ref,
			 u32 height, u32 width, bool uncompressed)
{
	unsigned int copies = 0;
	s16 copy[8 * 8];
	s16 stat;
	unsigned int i, j;

	if (uncompressed) {
		memcpy(ref, *rlco, width * height);
		*rlco += width * height / 2;
		return;
	}

	/*
	 * When decoding each macroblock the rlco pointer will be increased
	 * by 65 * 2 bytes worst-case.
	 * To avoid overflow the buffer has to be 65/64th of the actual raw
	 * image size, just in case someone feeds it malicious data.
	 */
	for (j = 0; j < height / 8; j++) {
		for (i = 0; i < width / 8; i++) {
			u8 *refp = ref + j * 8 * width + i * 8;

			if (copies) {
				memcpy(cf->de_fwht, copy, sizeof(copy));
				if (stat & PFRAME_BIT)
					add_deltas(cf->de_fwht, refp, width);
				fill_decoder_block(refp, cf->de_fwht, width);
				copies--;
				continue;
			}

			stat = derlc(rlco, cf->coeffs);

			if (stat & PFRAME_BIT)
				dequantize_inter(cf->coeffs);
			else
				dequantize_intra(cf->coeffs);

			ifwht(cf->coeffs, cf->de_fwht,
			      (stat & PFRAME_BIT) ? 0 : 1);

			copies = (stat & DUPS_MASK) >> 1;
			if (copies)
				memcpy(copy, cf->de_fwht, sizeof(copy));
			if (stat & PFRAME_BIT)
				add_deltas(cf->de_fwht, refp, width);
			fill_decoder_block(refp, cf->de_fwht, width);
		}
	}
}