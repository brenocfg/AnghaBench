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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  d ;

/* Variables and functions */
 int /*<<< orphan*/  c2p_32x8 (int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_planar (void*,int,int,int*) ; 
 int /*<<< orphan*/  store_planar_masked (void*,int,int,int*,int) ; 

void c2p_planar(void *dst, const void *src, u32 dx, u32 dy, u32 width,
		u32 height, u32 dst_nextline, u32 dst_nextplane,
		u32 src_nextline, u32 bpp)
{
	union {
		u8 pixels[32];
		u32 words[8];
	} d;
	u32 dst_idx, first, last, w;
	const u8 *c;
	void *p;

	dst += dy*dst_nextline+(dx & ~31);
	dst_idx = dx % 32;
	first = 0xffffffffU >> dst_idx;
	last = ~(0xffffffffU >> ((dst_idx+width) % 32));
	while (height--) {
		c = src;
		p = dst;
		w = width;
		if (dst_idx+width <= 32) {
			/* Single destination word */
			first &= last;
			memset(d.pixels, 0, sizeof(d));
			memcpy(d.pixels+dst_idx, c, width);
			c += width;
			c2p_32x8(d.words);
			store_planar_masked(p, dst_nextplane, bpp, d.words,
					    first);
			p += 4;
		} else {
			/* Multiple destination words */
			w = width;
			/* Leading bits */
			if (dst_idx) {
				w = 32 - dst_idx;
				memset(d.pixels, 0, dst_idx);
				memcpy(d.pixels+dst_idx, c, w);
				c += w;
				c2p_32x8(d.words);
				store_planar_masked(p, dst_nextplane, bpp,
						    d.words, first);
				p += 4;
				w = width-w;
			}
			/* Main chunk */
			while (w >= 32) {
				memcpy(d.pixels, c, 32);
				c += 32;
				c2p_32x8(d.words);
				store_planar(p, dst_nextplane, bpp, d.words);
				p += 4;
				w -= 32;
			}
			/* Trailing bits */
			w %= 32;
			if (w > 0) {
				memcpy(d.pixels, c, w);
				memset(d.pixels+w, 0, 32-w);
				c2p_32x8(d.words);
				store_planar_masked(p, dst_nextplane, bpp,
						    d.words, last);
			}
		}
		src += src_nextline;
		dst += dst_nextline;
	}
}