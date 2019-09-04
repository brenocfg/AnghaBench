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

/* Variables and functions */

u32 spu2_assoc_resp_len(enum spu_cipher_mode cipher_mode,
			unsigned int assoc_len, unsigned int iv_len,
			bool is_encrypt)
{
	u32 resp_len = assoc_len;

	if (is_encrypt)
		/* gcm aes esp has to write 8-byte IV in response */
		resp_len += iv_len;
	return resp_len;
}