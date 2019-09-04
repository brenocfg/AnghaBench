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
struct cc_cipher_ctx {int flow_mode; int /*<<< orphan*/  cipher_mode; } ;

/* Variables and functions */
 unsigned int AES_BLOCK_SIZE ; 
 unsigned int DES_BLOCK_SIZE ; 
#define  DRV_CIPHER_BITLOCKER 137 
#define  DRV_CIPHER_CBC 136 
#define  DRV_CIPHER_CBC_CTS 135 
#define  DRV_CIPHER_CTR 134 
#define  DRV_CIPHER_ECB 133 
#define  DRV_CIPHER_ESSIV 132 
#define  DRV_CIPHER_OFB 131 
#define  DRV_CIPHER_XTS 130 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int,unsigned int) ; 
#define  S_DIN_to_AES 129 
#define  S_DIN_to_DES 128 

__attribute__((used)) static int validate_data_size(struct cc_cipher_ctx *ctx_p,
			      unsigned int size)
{
	switch (ctx_p->flow_mode) {
	case S_DIN_to_AES:
		switch (ctx_p->cipher_mode) {
		case DRV_CIPHER_XTS:
			if (size >= AES_BLOCK_SIZE &&
			    IS_ALIGNED(size, AES_BLOCK_SIZE))
				return 0;
			break;
		case DRV_CIPHER_CBC_CTS:
			if (size >= AES_BLOCK_SIZE)
				return 0;
			break;
		case DRV_CIPHER_OFB:
		case DRV_CIPHER_CTR:
				return 0;
		case DRV_CIPHER_ECB:
		case DRV_CIPHER_CBC:
		case DRV_CIPHER_ESSIV:
		case DRV_CIPHER_BITLOCKER:
			if (IS_ALIGNED(size, AES_BLOCK_SIZE))
				return 0;
			break;
		default:
			break;
		}
		break;
	case S_DIN_to_DES:
		if (IS_ALIGNED(size, DES_BLOCK_SIZE))
			return 0;
		break;
	default:
		break;
	}
	return -EINVAL;
}