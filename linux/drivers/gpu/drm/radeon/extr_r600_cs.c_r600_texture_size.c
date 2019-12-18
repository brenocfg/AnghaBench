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
 unsigned int r600_fmt_get_blocksize (unsigned int) ; 
 unsigned int r600_fmt_get_nblocksx (unsigned int,unsigned int) ; 
 unsigned int r600_fmt_get_nblocksy (unsigned int,unsigned int) ; 
 unsigned int r600_mip_minify (unsigned int,unsigned int) ; 
 unsigned int round_up (unsigned int,unsigned int) ; 

__attribute__((used)) static void r600_texture_size(unsigned nfaces, unsigned blevel, unsigned llevel,
			      unsigned w0, unsigned h0, unsigned d0, unsigned nsamples, unsigned format,
			      unsigned block_align, unsigned height_align, unsigned base_align,
			      unsigned *l0_size, unsigned *mipmap_size)
{
	unsigned offset, i, level;
	unsigned width, height, depth, size;
	unsigned blocksize;
	unsigned nbx, nby;
	unsigned nlevels = llevel - blevel + 1;

	*l0_size = -1;
	blocksize = r600_fmt_get_blocksize(format);

	w0 = r600_mip_minify(w0, 0);
	h0 = r600_mip_minify(h0, 0);
	d0 = r600_mip_minify(d0, 0);
	for(i = 0, offset = 0, level = blevel; i < nlevels; i++, level++) {
		width = r600_mip_minify(w0, i);
		nbx = r600_fmt_get_nblocksx(format, width);

		nbx = round_up(nbx, block_align);

		height = r600_mip_minify(h0, i);
		nby = r600_fmt_get_nblocksy(format, height);
		nby = round_up(nby, height_align);

		depth = r600_mip_minify(d0, i);

		size = nbx * nby * blocksize * nsamples;
		if (nfaces)
			size *= nfaces;
		else
			size *= depth;

		if (i == 0)
			*l0_size = size;

		if (i == 0 || i == 1)
			offset = round_up(offset, base_align);

		offset += size;
	}
	*mipmap_size = offset;
	if (llevel == 0)
		*mipmap_size = *l0_size;
	if (!blevel)
		*mipmap_size -= *l0_size;
}