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

/* Variables and functions */
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int EINVAL ; 
 int ICP_QAT_HW_CIPHER_ALGO_AES128 ; 
 int ICP_QAT_HW_CIPHER_ALGO_AES192 ; 
 int ICP_QAT_HW_CIPHER_ALGO_AES256 ; 
 int ICP_QAT_HW_CIPHER_XTS_MODE ; 

__attribute__((used)) static int qat_alg_validate_key(int key_len, int *alg, int mode)
{
	if (mode != ICP_QAT_HW_CIPHER_XTS_MODE) {
		switch (key_len) {
		case AES_KEYSIZE_128:
			*alg = ICP_QAT_HW_CIPHER_ALGO_AES128;
			break;
		case AES_KEYSIZE_192:
			*alg = ICP_QAT_HW_CIPHER_ALGO_AES192;
			break;
		case AES_KEYSIZE_256:
			*alg = ICP_QAT_HW_CIPHER_ALGO_AES256;
			break;
		default:
			return -EINVAL;
		}
	} else {
		switch (key_len) {
		case AES_KEYSIZE_128 << 1:
			*alg = ICP_QAT_HW_CIPHER_ALGO_AES128;
			break;
		case AES_KEYSIZE_256 << 1:
			*alg = ICP_QAT_HW_CIPHER_ALGO_AES256;
			break;
		default:
			return -EINVAL;
		}
	}
	return 0;
}