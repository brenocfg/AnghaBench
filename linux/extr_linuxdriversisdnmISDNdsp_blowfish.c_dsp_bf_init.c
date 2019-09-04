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
typedef  int uint ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct dsp {int* bf_crypt_out; int bf_sync; int bf_enable; scalar_t__ bf_decrypt_out_pos; scalar_t__ bf_decrypt_in_pos; scalar_t__ bf_crypt_pos; int /*<<< orphan*/ * bf_data_out; scalar_t__ bf_s; scalar_t__ bf_p; } ;

/* Variables and functions */
 int* bf_pbox ; 
 int* bf_sbox ; 
 int /*<<< orphan*/  dsp_silence ; 
 int /*<<< orphan*/  encrypt_block (int*,int*,int*,int*) ; 

int
dsp_bf_init(struct dsp *dsp, const u8 *key, uint keylen)
{
	short i, j, count;
	u32 data[2], temp;
	u32 *P = (u32 *)dsp->bf_p;
	u32 *S = (u32 *)dsp->bf_s;

	if (keylen < 4 || keylen > 56)
		return 1;

	/* Set dsp states */
	i = 0;
	while (i < 9) {
		dsp->bf_crypt_out[i] = 0xff;
		dsp->bf_data_out[i] = dsp_silence;
		i++;
	}
	dsp->bf_crypt_pos = 0;
	dsp->bf_decrypt_in_pos = 0;
	dsp->bf_decrypt_out_pos = 0;
	dsp->bf_sync = 0x1ff;
	dsp->bf_enable = 1;

	/* Copy the initialization s-boxes */
	for (i = 0, count = 0; i < 256; i++)
		for (j = 0; j < 4; j++, count++)
			S[count] = bf_sbox[count];

	/* Set the p-boxes */
	for (i = 0; i < 16 + 2; i++)
		P[i] = bf_pbox[i];

	/* Actual subkey generation */
	for (j = 0, i = 0; i < 16 + 2; i++) {
		temp = (((u32)key[j] << 24) |
			((u32)key[(j + 1) % keylen] << 16) |
			((u32)key[(j + 2) % keylen] << 8) |
			((u32)key[(j + 3) % keylen]));

		P[i] = P[i] ^ temp;
		j = (j + 4) % keylen;
	}

	data[0] = 0x00000000;
	data[1] = 0x00000000;

	for (i = 0; i < 16 + 2; i += 2) {
		encrypt_block(P, S, data, data);

		P[i] = data[0];
		P[i + 1] = data[1];
	}

	for (i = 0; i < 4; i++) {
		for (j = 0, count = i * 256; j < 256; j += 2, count += 2) {
			encrypt_block(P, S, data, data);

			S[count] = data[0];
			S[count + 1] = data[1];
		}
	}

	return 0;
}