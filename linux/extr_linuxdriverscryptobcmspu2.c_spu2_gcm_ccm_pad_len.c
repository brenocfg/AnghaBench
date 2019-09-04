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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum spu_cipher_mode { ____Placeholder_spu_cipher_mode } spu_cipher_mode ;

/* Variables and functions */

u32 spu2_gcm_ccm_pad_len(enum spu_cipher_mode cipher_mode,
			 unsigned int data_size)
{
	return 0;
}