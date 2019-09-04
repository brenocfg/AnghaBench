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
typedef  unsigned int u32 ;
typedef  enum spu_cipher_mode { ____Placeholder_spu_cipher_mode } spu_cipher_mode ;
typedef  enum spu_cipher_alg { ____Placeholder_spu_cipher_alg } spu_cipher_alg ;

/* Variables and functions */
 int CIPHER_MODE_XTS ; 
 unsigned int SPUM_NSP_MAX_PAYLOAD ; 
 scalar_t__ SPU_XTS_TWEAK_SIZE ; 

u32 spum_nsp_ctx_max_payload(enum spu_cipher_alg cipher_alg,
			     enum spu_cipher_mode cipher_mode,
			     unsigned int blocksize)
{
	u32 max_payload = SPUM_NSP_MAX_PAYLOAD;
	u32 excess;

	/* In XTS on SPU-M, we'll need to insert tweak before input data */
	if (cipher_mode == CIPHER_MODE_XTS)
		max_payload -= SPU_XTS_TWEAK_SIZE;

	excess = max_payload % blocksize;

	return max_payload - excess;
}