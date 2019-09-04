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
struct cc_cipher_ctx {int flow_mode; int /*<<< orphan*/  cipher_mode; } ;

/* Variables and functions */
#define  CC_AES_128_BIT_KEY_SIZE 132 
#define  CC_AES_192_BIT_KEY_SIZE 131 
#define  CC_AES_256_BIT_KEY_SIZE 130 
 int /*<<< orphan*/  DES3_EDE_KEY_SIZE ; 
 int /*<<< orphan*/  DES_KEY_SIZE ; 
 int /*<<< orphan*/  DRV_CIPHER_BITLOCKER ; 
 int /*<<< orphan*/  DRV_CIPHER_ESSIV ; 
 int /*<<< orphan*/  DRV_CIPHER_XTS ; 
 int EINVAL ; 
#define  S_DIN_to_AES 129 
#define  S_DIN_to_DES 128 

__attribute__((used)) static int validate_keys_sizes(struct cc_cipher_ctx *ctx_p, u32 size)
{
	switch (ctx_p->flow_mode) {
	case S_DIN_to_AES:
		switch (size) {
		case CC_AES_128_BIT_KEY_SIZE:
		case CC_AES_192_BIT_KEY_SIZE:
			if (ctx_p->cipher_mode != DRV_CIPHER_XTS &&
			    ctx_p->cipher_mode != DRV_CIPHER_ESSIV &&
			    ctx_p->cipher_mode != DRV_CIPHER_BITLOCKER)
				return 0;
			break;
		case CC_AES_256_BIT_KEY_SIZE:
			return 0;
		case (CC_AES_192_BIT_KEY_SIZE * 2):
		case (CC_AES_256_BIT_KEY_SIZE * 2):
			if (ctx_p->cipher_mode == DRV_CIPHER_XTS ||
			    ctx_p->cipher_mode == DRV_CIPHER_ESSIV ||
			    ctx_p->cipher_mode == DRV_CIPHER_BITLOCKER)
				return 0;
			break;
		default:
			break;
		}
		break;
	case S_DIN_to_DES:
		if (size == DES3_EDE_KEY_SIZE || size == DES_KEY_SIZE)
			return 0;
		break;
	default:
		break;
	}
	return -EINVAL;
}