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
typedef  unsigned long u32 ;

/* Variables and functions */
 unsigned long DES_PC2 (unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ROL (unsigned long,int) ; 
 unsigned long* pc1 ; 
 unsigned long* pc2 ; 
 unsigned long* rs ; 

__attribute__((used)) static void dkey(u32 *pe, const u8 *k)
{
	/* K&R: long is at least 32 bits */
	unsigned long a, b, c, d;
	const u32 *pt = pc2;

	d = k[4]; d &= 0x0e; d <<= 4; d |= k[0] & 0x1e; d = pc1[d];
	c = k[5]; c &= 0x0e; c <<= 4; c |= k[1] & 0x1e; c = pc1[c];
	b = k[6]; b &= 0x0e; b <<= 4; b |= k[2] & 0x1e; b = pc1[b];
	a = k[7]; a &= 0x0e; a <<= 4; a |= k[3] & 0x1e; a = pc1[a];

	pe[ 0 * 2] = DES_PC2(a, b, c, d); d = rs[d];
	pe[ 1 * 2] = DES_PC2(d, a, b, c); c = rs[c]; b = rs[b];
	pe[ 2 * 2] = DES_PC2(b, c, d, a); a = rs[a]; d = rs[d];
	pe[ 3 * 2] = DES_PC2(d, a, b, c); c = rs[c]; b = rs[b];
	pe[ 4 * 2] = DES_PC2(b, c, d, a); a = rs[a]; d = rs[d];
	pe[ 5 * 2] = DES_PC2(d, a, b, c); c = rs[c]; b = rs[b];
	pe[ 6 * 2] = DES_PC2(b, c, d, a); a = rs[a]; d = rs[d];
	pe[ 7 * 2] = DES_PC2(d, a, b, c); c = rs[c];
	pe[ 8 * 2] = DES_PC2(c, d, a, b); b = rs[b]; a = rs[a];
	pe[ 9 * 2] = DES_PC2(a, b, c, d); d = rs[d]; c = rs[c];
	pe[10 * 2] = DES_PC2(c, d, a, b); b = rs[b]; a = rs[a];
	pe[11 * 2] = DES_PC2(a, b, c, d); d = rs[d]; c = rs[c];
	pe[12 * 2] = DES_PC2(c, d, a, b); b = rs[b]; a = rs[a];
	pe[13 * 2] = DES_PC2(a, b, c, d); d = rs[d]; c = rs[c];
	pe[14 * 2] = DES_PC2(c, d, a, b); b = rs[b];
	pe[15 * 2] = DES_PC2(b, c, d, a);

	/* Skip to next table set */
	pt += 512;

	d = k[0]; d &= 0xe0; d >>= 4; d |= k[4] & 0xf0; d = pc1[d + 1];
	c = k[1]; c &= 0xe0; c >>= 4; c |= k[5] & 0xf0; c = pc1[c + 1];
	b = k[2]; b &= 0xe0; b >>= 4; b |= k[6] & 0xf0; b = pc1[b + 1];
	a = k[3]; a &= 0xe0; a >>= 4; a |= k[7] & 0xf0; a = pc1[a + 1];

	pe[ 0 * 2 + 1] = DES_PC2(a, b, c, d); d = rs[d];
	pe[ 1 * 2 + 1] = DES_PC2(d, a, b, c); c = rs[c]; b = rs[b];
	pe[ 2 * 2 + 1] = DES_PC2(b, c, d, a); a = rs[a]; d = rs[d];
	pe[ 3 * 2 + 1] = DES_PC2(d, a, b, c); c = rs[c]; b = rs[b];
	pe[ 4 * 2 + 1] = DES_PC2(b, c, d, a); a = rs[a]; d = rs[d];
	pe[ 5 * 2 + 1] = DES_PC2(d, a, b, c); c = rs[c]; b = rs[b];
	pe[ 6 * 2 + 1] = DES_PC2(b, c, d, a); a = rs[a]; d = rs[d];
	pe[ 7 * 2 + 1] = DES_PC2(d, a, b, c); c = rs[c];
	pe[ 8 * 2 + 1] = DES_PC2(c, d, a, b); b = rs[b]; a = rs[a];
	pe[ 9 * 2 + 1] = DES_PC2(a, b, c, d); d = rs[d]; c = rs[c];
	pe[10 * 2 + 1] = DES_PC2(c, d, a, b); b = rs[b]; a = rs[a];
	pe[11 * 2 + 1] = DES_PC2(a, b, c, d); d = rs[d]; c = rs[c];
	pe[12 * 2 + 1] = DES_PC2(c, d, a, b); b = rs[b]; a = rs[a];
	pe[13 * 2 + 1] = DES_PC2(a, b, c, d); d = rs[d]; c = rs[c];
	pe[14 * 2 + 1] = DES_PC2(c, d, a, b); b = rs[b];
	pe[15 * 2 + 1] = DES_PC2(b, c, d, a);

	/* Fixup: 2413 5768 -> 1357 2468 */
	for (d = 0; d < 16; ++d) {
		a = pe[2 * d];
		b = pe[2 * d + 1];
		c = a ^ b;
		c &= 0xffff0000;
		a ^= c;
		b ^= c;
		ROL(b, 18);
		pe[2 * d] = a;
		pe[2 * d + 1] = b;
	}
}