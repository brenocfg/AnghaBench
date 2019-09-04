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
struct pwc_dec23_private {unsigned char const* stream; unsigned char** table_0004_pass1; unsigned char** table_8004_pass1; unsigned char** table_0004_pass2; unsigned char** table_8004_pass2; int /*<<< orphan*/  scalebits; int /*<<< orphan*/  temp_colors; scalar_t__ nbits_in_reservoir; scalar_t__ reservoir; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_image_block_CrCb (int /*<<< orphan*/ ,unsigned char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_image_block_Y (int /*<<< orphan*/ ,unsigned char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_block (struct pwc_dec23_private*,unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/  get_nbits (struct pwc_dec23_private*,int,int) ; 

__attribute__((used)) static void DecompressBand23(struct pwc_dec23_private *pdec,
			     const unsigned char *rawyuv,
			     unsigned char *planar_y,
			     unsigned char *planar_u,
			     unsigned char *planar_v,
			     unsigned int   compressed_image_width,
			     unsigned int   real_image_width)
{
	int compression_index, nblocks;
	const unsigned char *ptable0004;
	const unsigned char *ptable8004;

	pdec->reservoir = 0;
	pdec->nbits_in_reservoir = 0;
	pdec->stream = rawyuv + 1;	/* The first byte of the stream is skipped */

	get_nbits(pdec, 4, compression_index);

	/* pass 1: uncompress Y component */
	nblocks = compressed_image_width / 4;

	ptable0004 = pdec->table_0004_pass1[compression_index];
	ptable8004 = pdec->table_8004_pass1[compression_index];

	/* Each block decode a square of 4x4 */
	while (nblocks) {
		decode_block(pdec, ptable0004, ptable8004);
		copy_image_block_Y(pdec->temp_colors, planar_y, real_image_width, pdec->scalebits);
		planar_y += 4;
		nblocks--;
	}

	/* pass 2: uncompress UV component */
	nblocks = compressed_image_width / 8;

	ptable0004 = pdec->table_0004_pass2[compression_index];
	ptable8004 = pdec->table_8004_pass2[compression_index];

	/* Each block decode a square of 4x4 */
	while (nblocks) {
		decode_block(pdec, ptable0004, ptable8004);
		copy_image_block_CrCb(pdec->temp_colors, planar_u, real_image_width/2, pdec->scalebits);

		decode_block(pdec, ptable0004, ptable8004);
		copy_image_block_CrCb(pdec->temp_colors, planar_v, real_image_width/2, pdec->scalebits);

		planar_v += 8;
		planar_u += 8;
		nblocks -= 2;
	}

}