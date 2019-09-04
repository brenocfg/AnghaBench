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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  F1 ; 
 int /*<<< orphan*/  F2 ; 
 int /*<<< orphan*/  F3 ; 
 int /*<<< orphan*/  F4 ; 
 int /*<<< orphan*/  K1 ; 
 int /*<<< orphan*/  K2 ; 
 int /*<<< orphan*/  K3 ; 
 int /*<<< orphan*/  K4 ; 
 int /*<<< orphan*/  KK1 ; 
 int /*<<< orphan*/  KK2 ; 
 int /*<<< orphan*/  KK3 ; 
 int /*<<< orphan*/  KK4 ; 
 int /*<<< orphan*/  ROUND (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  swap (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void rmd256_transform(u32 *state, const __le32 *in)
{
	u32 aa, bb, cc, dd, aaa, bbb, ccc, ddd;

	/* Initialize left lane */
	aa = state[0];
	bb = state[1];
	cc = state[2];
	dd = state[3];

	/* Initialize right lane */
	aaa = state[4];
	bbb = state[5];
	ccc = state[6];
	ddd = state[7];

	/* round 1: left lane */
	ROUND(aa, bb, cc, dd, F1, K1, in[0],  11);
	ROUND(dd, aa, bb, cc, F1, K1, in[1],  14);
	ROUND(cc, dd, aa, bb, F1, K1, in[2],  15);
	ROUND(bb, cc, dd, aa, F1, K1, in[3],  12);
	ROUND(aa, bb, cc, dd, F1, K1, in[4],   5);
	ROUND(dd, aa, bb, cc, F1, K1, in[5],   8);
	ROUND(cc, dd, aa, bb, F1, K1, in[6],   7);
	ROUND(bb, cc, dd, aa, F1, K1, in[7],   9);
	ROUND(aa, bb, cc, dd, F1, K1, in[8],  11);
	ROUND(dd, aa, bb, cc, F1, K1, in[9],  13);
	ROUND(cc, dd, aa, bb, F1, K1, in[10], 14);
	ROUND(bb, cc, dd, aa, F1, K1, in[11], 15);
	ROUND(aa, bb, cc, dd, F1, K1, in[12],  6);
	ROUND(dd, aa, bb, cc, F1, K1, in[13],  7);
	ROUND(cc, dd, aa, bb, F1, K1, in[14],  9);
	ROUND(bb, cc, dd, aa, F1, K1, in[15],  8);

	/* round 1: right lane */
	ROUND(aaa, bbb, ccc, ddd, F4, KK1, in[5],   8);
	ROUND(ddd, aaa, bbb, ccc, F4, KK1, in[14],  9);
	ROUND(ccc, ddd, aaa, bbb, F4, KK1, in[7],   9);
	ROUND(bbb, ccc, ddd, aaa, F4, KK1, in[0],  11);
	ROUND(aaa, bbb, ccc, ddd, F4, KK1, in[9],  13);
	ROUND(ddd, aaa, bbb, ccc, F4, KK1, in[2],  15);
	ROUND(ccc, ddd, aaa, bbb, F4, KK1, in[11], 15);
	ROUND(bbb, ccc, ddd, aaa, F4, KK1, in[4],   5);
	ROUND(aaa, bbb, ccc, ddd, F4, KK1, in[13],  7);
	ROUND(ddd, aaa, bbb, ccc, F4, KK1, in[6],   7);
	ROUND(ccc, ddd, aaa, bbb, F4, KK1, in[15],  8);
	ROUND(bbb, ccc, ddd, aaa, F4, KK1, in[8],  11);
	ROUND(aaa, bbb, ccc, ddd, F4, KK1, in[1],  14);
	ROUND(ddd, aaa, bbb, ccc, F4, KK1, in[10], 14);
	ROUND(ccc, ddd, aaa, bbb, F4, KK1, in[3],  12);
	ROUND(bbb, ccc, ddd, aaa, F4, KK1, in[12],  6);

	/* Swap contents of "a" registers */
	swap(aa, aaa);

	/* round 2: left lane */
	ROUND(aa, bb, cc, dd, F2, K2, in[7],   7);
	ROUND(dd, aa, bb, cc, F2, K2, in[4],   6);
	ROUND(cc, dd, aa, bb, F2, K2, in[13],  8);
	ROUND(bb, cc, dd, aa, F2, K2, in[1],  13);
	ROUND(aa, bb, cc, dd, F2, K2, in[10], 11);
	ROUND(dd, aa, bb, cc, F2, K2, in[6],   9);
	ROUND(cc, dd, aa, bb, F2, K2, in[15],  7);
	ROUND(bb, cc, dd, aa, F2, K2, in[3],  15);
	ROUND(aa, bb, cc, dd, F2, K2, in[12],  7);
	ROUND(dd, aa, bb, cc, F2, K2, in[0],  12);
	ROUND(cc, dd, aa, bb, F2, K2, in[9],  15);
	ROUND(bb, cc, dd, aa, F2, K2, in[5],   9);
	ROUND(aa, bb, cc, dd, F2, K2, in[2],  11);
	ROUND(dd, aa, bb, cc, F2, K2, in[14],  7);
	ROUND(cc, dd, aa, bb, F2, K2, in[11], 13);
	ROUND(bb, cc, dd, aa, F2, K2, in[8],  12);

	/* round 2: right lane */
	ROUND(aaa, bbb, ccc, ddd, F3, KK2, in[6],   9);
	ROUND(ddd, aaa, bbb, ccc, F3, KK2, in[11], 13);
	ROUND(ccc, ddd, aaa, bbb, F3, KK2, in[3],  15);
	ROUND(bbb, ccc, ddd, aaa, F3, KK2, in[7],   7);
	ROUND(aaa, bbb, ccc, ddd, F3, KK2, in[0],  12);
	ROUND(ddd, aaa, bbb, ccc, F3, KK2, in[13],  8);
	ROUND(ccc, ddd, aaa, bbb, F3, KK2, in[5],   9);
	ROUND(bbb, ccc, ddd, aaa, F3, KK2, in[10], 11);
	ROUND(aaa, bbb, ccc, ddd, F3, KK2, in[14],  7);
	ROUND(ddd, aaa, bbb, ccc, F3, KK2, in[15],  7);
	ROUND(ccc, ddd, aaa, bbb, F3, KK2, in[8],  12);
	ROUND(bbb, ccc, ddd, aaa, F3, KK2, in[12],  7);
	ROUND(aaa, bbb, ccc, ddd, F3, KK2, in[4],   6);
	ROUND(ddd, aaa, bbb, ccc, F3, KK2, in[9],  15);
	ROUND(ccc, ddd, aaa, bbb, F3, KK2, in[1],  13);
	ROUND(bbb, ccc, ddd, aaa, F3, KK2, in[2],  11);

	/* Swap contents of "b" registers */
	swap(bb, bbb);

	/* round 3: left lane */
	ROUND(aa, bb, cc, dd, F3, K3, in[3],  11);
	ROUND(dd, aa, bb, cc, F3, K3, in[10], 13);
	ROUND(cc, dd, aa, bb, F3, K3, in[14],  6);
	ROUND(bb, cc, dd, aa, F3, K3, in[4],   7);
	ROUND(aa, bb, cc, dd, F3, K3, in[9],  14);
	ROUND(dd, aa, bb, cc, F3, K3, in[15],  9);
	ROUND(cc, dd, aa, bb, F3, K3, in[8],  13);
	ROUND(bb, cc, dd, aa, F3, K3, in[1],  15);
	ROUND(aa, bb, cc, dd, F3, K3, in[2],  14);
	ROUND(dd, aa, bb, cc, F3, K3, in[7],   8);
	ROUND(cc, dd, aa, bb, F3, K3, in[0],  13);
	ROUND(bb, cc, dd, aa, F3, K3, in[6],   6);
	ROUND(aa, bb, cc, dd, F3, K3, in[13],  5);
	ROUND(dd, aa, bb, cc, F3, K3, in[11], 12);
	ROUND(cc, dd, aa, bb, F3, K3, in[5],   7);
	ROUND(bb, cc, dd, aa, F3, K3, in[12],  5);

	/* round 3: right lane */
	ROUND(aaa, bbb, ccc, ddd, F2, KK3, in[15],  9);
	ROUND(ddd, aaa, bbb, ccc, F2, KK3, in[5],   7);
	ROUND(ccc, ddd, aaa, bbb, F2, KK3, in[1],  15);
	ROUND(bbb, ccc, ddd, aaa, F2, KK3, in[3],  11);
	ROUND(aaa, bbb, ccc, ddd, F2, KK3, in[7],   8);
	ROUND(ddd, aaa, bbb, ccc, F2, KK3, in[14],  6);
	ROUND(ccc, ddd, aaa, bbb, F2, KK3, in[6],   6);
	ROUND(bbb, ccc, ddd, aaa, F2, KK3, in[9],  14);
	ROUND(aaa, bbb, ccc, ddd, F2, KK3, in[11], 12);
	ROUND(ddd, aaa, bbb, ccc, F2, KK3, in[8],  13);
	ROUND(ccc, ddd, aaa, bbb, F2, KK3, in[12],  5);
	ROUND(bbb, ccc, ddd, aaa, F2, KK3, in[2],  14);
	ROUND(aaa, bbb, ccc, ddd, F2, KK3, in[10], 13);
	ROUND(ddd, aaa, bbb, ccc, F2, KK3, in[0],  13);
	ROUND(ccc, ddd, aaa, bbb, F2, KK3, in[4],   7);
	ROUND(bbb, ccc, ddd, aaa, F2, KK3, in[13],  5);

	/* Swap contents of "c" registers */
	swap(cc, ccc);

	/* round 4: left lane */
	ROUND(aa, bb, cc, dd, F4, K4, in[1],  11);
	ROUND(dd, aa, bb, cc, F4, K4, in[9],  12);
	ROUND(cc, dd, aa, bb, F4, K4, in[11], 14);
	ROUND(bb, cc, dd, aa, F4, K4, in[10], 15);
	ROUND(aa, bb, cc, dd, F4, K4, in[0],  14);
	ROUND(dd, aa, bb, cc, F4, K4, in[8],  15);
	ROUND(cc, dd, aa, bb, F4, K4, in[12],  9);
	ROUND(bb, cc, dd, aa, F4, K4, in[4],   8);
	ROUND(aa, bb, cc, dd, F4, K4, in[13],  9);
	ROUND(dd, aa, bb, cc, F4, K4, in[3],  14);
	ROUND(cc, dd, aa, bb, F4, K4, in[7],   5);
	ROUND(bb, cc, dd, aa, F4, K4, in[15],  6);
	ROUND(aa, bb, cc, dd, F4, K4, in[14],  8);
	ROUND(dd, aa, bb, cc, F4, K4, in[5],   6);
	ROUND(cc, dd, aa, bb, F4, K4, in[6],   5);
	ROUND(bb, cc, dd, aa, F4, K4, in[2],  12);

	/* round 4: right lane */
	ROUND(aaa, bbb, ccc, ddd, F1, KK4, in[8],  15);
	ROUND(ddd, aaa, bbb, ccc, F1, KK4, in[6],   5);
	ROUND(ccc, ddd, aaa, bbb, F1, KK4, in[4],   8);
	ROUND(bbb, ccc, ddd, aaa, F1, KK4, in[1],  11);
	ROUND(aaa, bbb, ccc, ddd, F1, KK4, in[3],  14);
	ROUND(ddd, aaa, bbb, ccc, F1, KK4, in[11], 14);
	ROUND(ccc, ddd, aaa, bbb, F1, KK4, in[15],  6);
	ROUND(bbb, ccc, ddd, aaa, F1, KK4, in[0],  14);
	ROUND(aaa, bbb, ccc, ddd, F1, KK4, in[5],   6);
	ROUND(ddd, aaa, bbb, ccc, F1, KK4, in[12],  9);
	ROUND(ccc, ddd, aaa, bbb, F1, KK4, in[2],  12);
	ROUND(bbb, ccc, ddd, aaa, F1, KK4, in[13],  9);
	ROUND(aaa, bbb, ccc, ddd, F1, KK4, in[9],  12);
	ROUND(ddd, aaa, bbb, ccc, F1, KK4, in[7],   5);
	ROUND(ccc, ddd, aaa, bbb, F1, KK4, in[10], 15);
	ROUND(bbb, ccc, ddd, aaa, F1, KK4, in[14],  8);

	/* Swap contents of "d" registers */
	swap(dd, ddd);

	/* combine results */
	state[0] += aa;
	state[1] += bb;
	state[2] += cc;
	state[3] += dd;
	state[4] += aaa;
	state[5] += bbb;
	state[6] += ccc;
	state[7] += ddd;
}