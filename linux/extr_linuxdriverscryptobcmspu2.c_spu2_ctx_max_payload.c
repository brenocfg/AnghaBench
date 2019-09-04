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
 int CIPHER_ALG_AES ; 
 int CIPHER_MODE_CCM ; 
 unsigned int SPU2_MAX_PAYLOAD ; 
 unsigned int SPU_MAX_PAYLOAD_INF ; 

u32 spu2_ctx_max_payload(enum spu_cipher_alg cipher_alg,
			 enum spu_cipher_mode cipher_mode,
			 unsigned int blocksize)
{
	if ((cipher_alg == CIPHER_ALG_AES) &&
	    (cipher_mode == CIPHER_MODE_CCM)) {
		u32 excess = SPU2_MAX_PAYLOAD % blocksize;

		return SPU2_MAX_PAYLOAD - excess;
	} else {
		return SPU_MAX_PAYLOAD_INF;
	}
}