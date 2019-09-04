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
typedef  int u64 ;
struct wp512_ctx {int* hash; scalar_t__ buffer; } ;
typedef  int /*<<< orphan*/  state ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  K ;

/* Variables and functions */
 int* C0 ; 
 int* C1 ; 
 int* C2 ; 
 int* C3 ; 
 int* C4 ; 
 int* C5 ; 
 int* C6 ; 
 int* C7 ; 
 int WHIRLPOOL_ROUNDS ; 
 int be64_to_cpu (int /*<<< orphan*/  const) ; 
 int* rc ; 

__attribute__((used)) static void wp512_process_buffer(struct wp512_ctx *wctx) {
	int i, r;
	u64 K[8];        /* the round key */
	u64 block[8];    /* mu(buffer) */
	u64 state[8];    /* the cipher state */
	u64 L[8];
	const __be64 *buffer = (const __be64 *)wctx->buffer;

	for (i = 0; i < 8; i++)
		block[i] = be64_to_cpu(buffer[i]);

	state[0] = block[0] ^ (K[0] = wctx->hash[0]);
	state[1] = block[1] ^ (K[1] = wctx->hash[1]);
	state[2] = block[2] ^ (K[2] = wctx->hash[2]);
	state[3] = block[3] ^ (K[3] = wctx->hash[3]);
	state[4] = block[4] ^ (K[4] = wctx->hash[4]);
	state[5] = block[5] ^ (K[5] = wctx->hash[5]);
	state[6] = block[6] ^ (K[6] = wctx->hash[6]);
	state[7] = block[7] ^ (K[7] = wctx->hash[7]);

	for (r = 0; r < WHIRLPOOL_ROUNDS; r++) {

		L[0] = C0[(int)(K[0] >> 56)       ] ^
			   C1[(int)(K[7] >> 48) & 0xff] ^
			   C2[(int)(K[6] >> 40) & 0xff] ^
			   C3[(int)(K[5] >> 32) & 0xff] ^
			   C4[(int)(K[4] >> 24) & 0xff] ^
			   C5[(int)(K[3] >> 16) & 0xff] ^
			   C6[(int)(K[2] >>  8) & 0xff] ^
			   C7[(int)(K[1]      ) & 0xff] ^
			   rc[r];

		L[1] = C0[(int)(K[1] >> 56)       ] ^
			   C1[(int)(K[0] >> 48) & 0xff] ^
			   C2[(int)(K[7] >> 40) & 0xff] ^
			   C3[(int)(K[6] >> 32) & 0xff] ^
			   C4[(int)(K[5] >> 24) & 0xff] ^
			   C5[(int)(K[4] >> 16) & 0xff] ^
			   C6[(int)(K[3] >>  8) & 0xff] ^
			   C7[(int)(K[2]      ) & 0xff];

		L[2] = C0[(int)(K[2] >> 56)       ] ^
			   C1[(int)(K[1] >> 48) & 0xff] ^
			   C2[(int)(K[0] >> 40) & 0xff] ^
			   C3[(int)(K[7] >> 32) & 0xff] ^
			   C4[(int)(K[6] >> 24) & 0xff] ^
			   C5[(int)(K[5] >> 16) & 0xff] ^
			   C6[(int)(K[4] >>  8) & 0xff] ^
			   C7[(int)(K[3]      ) & 0xff];

		L[3] = C0[(int)(K[3] >> 56)       ] ^
			   C1[(int)(K[2] >> 48) & 0xff] ^
			   C2[(int)(K[1] >> 40) & 0xff] ^
			   C3[(int)(K[0] >> 32) & 0xff] ^
			   C4[(int)(K[7] >> 24) & 0xff] ^
			   C5[(int)(K[6] >> 16) & 0xff] ^
			   C6[(int)(K[5] >>  8) & 0xff] ^
			   C7[(int)(K[4]      ) & 0xff];

		L[4] = C0[(int)(K[4] >> 56)       ] ^
			   C1[(int)(K[3] >> 48) & 0xff] ^
			   C2[(int)(K[2] >> 40) & 0xff] ^
			   C3[(int)(K[1] >> 32) & 0xff] ^
			   C4[(int)(K[0] >> 24) & 0xff] ^
			   C5[(int)(K[7] >> 16) & 0xff] ^
			   C6[(int)(K[6] >>  8) & 0xff] ^
			   C7[(int)(K[5]      ) & 0xff];

		L[5] = C0[(int)(K[5] >> 56)       ] ^
			   C1[(int)(K[4] >> 48) & 0xff] ^
			   C2[(int)(K[3] >> 40) & 0xff] ^
			   C3[(int)(K[2] >> 32) & 0xff] ^
			   C4[(int)(K[1] >> 24) & 0xff] ^
			   C5[(int)(K[0] >> 16) & 0xff] ^
			   C6[(int)(K[7] >>  8) & 0xff] ^
			   C7[(int)(K[6]      ) & 0xff];

		L[6] = C0[(int)(K[6] >> 56)       ] ^
			   C1[(int)(K[5] >> 48) & 0xff] ^
			   C2[(int)(K[4] >> 40) & 0xff] ^
			   C3[(int)(K[3] >> 32) & 0xff] ^
			   C4[(int)(K[2] >> 24) & 0xff] ^
			   C5[(int)(K[1] >> 16) & 0xff] ^
			   C6[(int)(K[0] >>  8) & 0xff] ^
			   C7[(int)(K[7]      ) & 0xff];

		L[7] = C0[(int)(K[7] >> 56)       ] ^
			   C1[(int)(K[6] >> 48) & 0xff] ^
			   C2[(int)(K[5] >> 40) & 0xff] ^
			   C3[(int)(K[4] >> 32) & 0xff] ^
			   C4[(int)(K[3] >> 24) & 0xff] ^
			   C5[(int)(K[2] >> 16) & 0xff] ^
			   C6[(int)(K[1] >>  8) & 0xff] ^
			   C7[(int)(K[0]      ) & 0xff];

		K[0] = L[0];
		K[1] = L[1];
		K[2] = L[2];
		K[3] = L[3];
		K[4] = L[4];
		K[5] = L[5];
		K[6] = L[6];
		K[7] = L[7];

		L[0] = C0[(int)(state[0] >> 56)       ] ^
			   C1[(int)(state[7] >> 48) & 0xff] ^
			   C2[(int)(state[6] >> 40) & 0xff] ^
			   C3[(int)(state[5] >> 32) & 0xff] ^
			   C4[(int)(state[4] >> 24) & 0xff] ^
			   C5[(int)(state[3] >> 16) & 0xff] ^
			   C6[(int)(state[2] >>  8) & 0xff] ^
			   C7[(int)(state[1]      ) & 0xff] ^
			   K[0];

		L[1] = C0[(int)(state[1] >> 56)       ] ^
			   C1[(int)(state[0] >> 48) & 0xff] ^
			   C2[(int)(state[7] >> 40) & 0xff] ^
			   C3[(int)(state[6] >> 32) & 0xff] ^
			   C4[(int)(state[5] >> 24) & 0xff] ^
			   C5[(int)(state[4] >> 16) & 0xff] ^
			   C6[(int)(state[3] >>  8) & 0xff] ^
			   C7[(int)(state[2]      ) & 0xff] ^
			   K[1];

		L[2] = C0[(int)(state[2] >> 56)       ] ^
			   C1[(int)(state[1] >> 48) & 0xff] ^
			   C2[(int)(state[0] >> 40) & 0xff] ^
			   C3[(int)(state[7] >> 32) & 0xff] ^
			   C4[(int)(state[6] >> 24) & 0xff] ^
			   C5[(int)(state[5] >> 16) & 0xff] ^
			   C6[(int)(state[4] >>  8) & 0xff] ^
			   C7[(int)(state[3]      ) & 0xff] ^
			   K[2];

		L[3] = C0[(int)(state[3] >> 56)       ] ^
			   C1[(int)(state[2] >> 48) & 0xff] ^
			   C2[(int)(state[1] >> 40) & 0xff] ^
			   C3[(int)(state[0] >> 32) & 0xff] ^
			   C4[(int)(state[7] >> 24) & 0xff] ^
			   C5[(int)(state[6] >> 16) & 0xff] ^
			   C6[(int)(state[5] >>  8) & 0xff] ^
			   C7[(int)(state[4]      ) & 0xff] ^
			   K[3];

		L[4] = C0[(int)(state[4] >> 56)       ] ^
			   C1[(int)(state[3] >> 48) & 0xff] ^
			   C2[(int)(state[2] >> 40) & 0xff] ^
			   C3[(int)(state[1] >> 32) & 0xff] ^
			   C4[(int)(state[0] >> 24) & 0xff] ^
			   C5[(int)(state[7] >> 16) & 0xff] ^
			   C6[(int)(state[6] >>  8) & 0xff] ^
			   C7[(int)(state[5]      ) & 0xff] ^
			   K[4];

		L[5] = C0[(int)(state[5] >> 56)       ] ^
			   C1[(int)(state[4] >> 48) & 0xff] ^
			   C2[(int)(state[3] >> 40) & 0xff] ^
			   C3[(int)(state[2] >> 32) & 0xff] ^
			   C4[(int)(state[1] >> 24) & 0xff] ^
			   C5[(int)(state[0] >> 16) & 0xff] ^
			   C6[(int)(state[7] >>  8) & 0xff] ^
			   C7[(int)(state[6]      ) & 0xff] ^
			   K[5];

		L[6] = C0[(int)(state[6] >> 56)       ] ^
			   C1[(int)(state[5] >> 48) & 0xff] ^
			   C2[(int)(state[4] >> 40) & 0xff] ^
			   C3[(int)(state[3] >> 32) & 0xff] ^
			   C4[(int)(state[2] >> 24) & 0xff] ^
			   C5[(int)(state[1] >> 16) & 0xff] ^
			   C6[(int)(state[0] >>  8) & 0xff] ^
			   C7[(int)(state[7]      ) & 0xff] ^
			   K[6];

		L[7] = C0[(int)(state[7] >> 56)       ] ^
			   C1[(int)(state[6] >> 48) & 0xff] ^
			   C2[(int)(state[5] >> 40) & 0xff] ^
			   C3[(int)(state[4] >> 32) & 0xff] ^
			   C4[(int)(state[3] >> 24) & 0xff] ^
			   C5[(int)(state[2] >> 16) & 0xff] ^
			   C6[(int)(state[1] >>  8) & 0xff] ^
			   C7[(int)(state[0]      ) & 0xff] ^
			   K[7];

		state[0] = L[0];
		state[1] = L[1];
		state[2] = L[2];
		state[3] = L[3];
		state[4] = L[4];
		state[5] = L[5];
		state[6] = L[6];
		state[7] = L[7];
	}
	/*
	* apply the Miyaguchi-Preneel compression function:
	*/
	wctx->hash[0] ^= state[0] ^ block[0];
	wctx->hash[1] ^= state[1] ^ block[1];
	wctx->hash[2] ^= state[2] ^ block[2];
	wctx->hash[3] ^= state[3] ^ block[3];
	wctx->hash[4] ^= state[4] ^ block[4];
	wctx->hash[5] ^= state[5] ^ block[5];
	wctx->hash[6] ^= state[6] ^ block[6];
	wctx->hash[7] ^= state[7] ^ block[7];

}