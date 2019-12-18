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
struct fb_info {int dummy; } ;

/* Variables and functions */
 unsigned long FB_SHIFT_HIGH (struct fb_info*,unsigned long,unsigned int) ; 
 unsigned long comp (unsigned long const,unsigned long,unsigned long) ; 

__attribute__((used)) static void
bitcpy(struct fb_info *p, unsigned long *dst, unsigned dst_idx,
	const unsigned long *src, unsigned src_idx, int bits, unsigned n)
{
	unsigned long first, last;
	int const shift = dst_idx-src_idx;
	int left, right;

	first = FB_SHIFT_HIGH(p, ~0UL, dst_idx);
	last = ~(FB_SHIFT_HIGH(p, ~0UL, (dst_idx+n) % bits));

	if (!shift) {
		/* Same alignment for source and dest */
		if (dst_idx+n <= bits) {
			/* Single word */
			if (last)
				first &= last;
			*dst = comp(*src, *dst, first);
		} else {
			/* Multiple destination words */
			/* Leading bits */
 			if (first != ~0UL) {
				*dst = comp(*src, *dst, first);
				dst++;
				src++;
				n -= bits - dst_idx;
			}

			/* Main chunk */
			n /= bits;
			while (n >= 8) {
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				n -= 8;
			}
			while (n--)
				*dst++ = *src++;

			/* Trailing bits */
			if (last)
				*dst = comp(*src, *dst, last);
		}
	} else {
		unsigned long d0, d1;
		int m;

		/* Different alignment for source and dest */
		right = shift & (bits - 1);
		left = -shift & (bits - 1);

		if (dst_idx+n <= bits) {
			/* Single destination word */
			if (last)
				first &= last;
			if (shift > 0) {
				/* Single source word */
				*dst = comp(*src << left, *dst, first);
			} else if (src_idx+n <= bits) {
				/* Single source word */
				*dst = comp(*src >> right, *dst, first);
			} else {
				/* 2 source words */
				d0 = *src++;
				d1 = *src;
				*dst = comp(d0 >> right | d1 << left, *dst,
					    first);
			}
		} else {
			/* Multiple destination words */
			/** We must always remember the last value read,
			    because in case SRC and DST overlap bitwise (e.g.
			    when moving just one pixel in 1bpp), we always
			    collect one full long for DST and that might
			    overlap with the current long from SRC. We store
			    this value in 'd0'. */
			d0 = *src++;
			/* Leading bits */
			if (shift > 0) {
				/* Single source word */
				*dst = comp(d0 << left, *dst, first);
				dst++;
				n -= bits - dst_idx;
			} else {
				/* 2 source words */
				d1 = *src++;
				*dst = comp(d0 >> right | d1 << left, *dst,
					    first);
				d0 = d1;
				dst++;
				n -= bits - dst_idx;
			}

			/* Main chunk */
			m = n % bits;
			n /= bits;
			while (n >= 4) {
				d1 = *src++;
				*dst++ = d0 >> right | d1 << left;
				d0 = d1;
				d1 = *src++;
				*dst++ = d0 >> right | d1 << left;
				d0 = d1;
				d1 = *src++;
				*dst++ = d0 >> right | d1 << left;
				d0 = d1;
				d1 = *src++;
				*dst++ = d0 >> right | d1 << left;
				d0 = d1;
				n -= 4;
			}
			while (n--) {
				d1 = *src++;
				*dst++ = d0 >> right | d1 << left;
				d0 = d1;
			}

			/* Trailing bits */
			if (m) {
				if (m <= bits - right) {
					/* Single source word */
					d0 >>= right;
				} else {
					/* 2 source words */
 					d1 = *src;
					d0 = d0 >> right | d1 << left;
				}
				*dst = comp(d0, *dst, last);
			}
		}
	}
}