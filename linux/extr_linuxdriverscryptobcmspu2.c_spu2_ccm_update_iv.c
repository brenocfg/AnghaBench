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
struct spu_cipher_parms {int* iv_buf; int iv_len; } ;

/* Variables and functions */
 int CCM_B0_L_PRIME ; 
 int CCM_B0_L_PRIME_SHIFT ; 
 int CCM_ESP_L_VALUE ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 

void spu2_ccm_update_iv(unsigned int digestsize,
			struct spu_cipher_parms *cipher_parms,
			unsigned int assoclen, unsigned int chunksize,
			bool is_encrypt, bool is_esp)
{
	int L;  /* size of length field, in bytes */

	/*
	 * In RFC4309 mode, L is fixed at 4 bytes; otherwise, IV from
	 * testmgr contains (L-1) in bottom 3 bits of first byte,
	 * per RFC 3610.
	 */
	if (is_esp)
		L = CCM_ESP_L_VALUE;
	else
		L = ((cipher_parms->iv_buf[0] & CCM_B0_L_PRIME) >>
		      CCM_B0_L_PRIME_SHIFT) + 1;

	/* SPU2 doesn't want these length bytes nor the first byte... */
	cipher_parms->iv_len -= (1 + L);
	memmove(cipher_parms->iv_buf, &cipher_parms->iv_buf[1],
		cipher_parms->iv_len);
}