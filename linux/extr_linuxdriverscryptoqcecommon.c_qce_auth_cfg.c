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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ AES_KEYSIZE_128 ; 
 scalar_t__ AES_KEYSIZE_256 ; 
 scalar_t__ AUTH_ALG_AES ; 
 scalar_t__ AUTH_ALG_SHA ; 
 scalar_t__ AUTH_ALG_SHIFT ; 
 int /*<<< orphan*/  AUTH_FIRST_SHIFT ; 
 scalar_t__ AUTH_KEY_SIZE_SHIFT ; 
 scalar_t__ AUTH_KEY_SZ_AES128 ; 
 scalar_t__ AUTH_KEY_SZ_AES256 ; 
 int /*<<< orphan*/  AUTH_LAST_SHIFT ; 
 scalar_t__ AUTH_MODE_CCM ; 
 scalar_t__ AUTH_MODE_CMAC ; 
 scalar_t__ AUTH_MODE_HASH ; 
 scalar_t__ AUTH_MODE_HMAC ; 
 scalar_t__ AUTH_MODE_SHIFT ; 
 scalar_t__ AUTH_NONCE_NUM_WORDS_SHIFT ; 
 scalar_t__ AUTH_POS_BEFORE ; 
 scalar_t__ AUTH_POS_SHIFT ; 
 scalar_t__ AUTH_SIZE_ENUM_16_BYTES ; 
 scalar_t__ AUTH_SIZE_SHA1 ; 
 scalar_t__ AUTH_SIZE_SHA256 ; 
 scalar_t__ AUTH_SIZE_SHIFT ; 
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_AES (unsigned long) ; 
 scalar_t__ IS_CBC (unsigned long) ; 
 scalar_t__ IS_CCM (unsigned long) ; 
 scalar_t__ IS_CMAC (unsigned long) ; 
 scalar_t__ IS_CTR (unsigned long) ; 
 scalar_t__ IS_SHA (unsigned long) ; 
 scalar_t__ IS_SHA1 (unsigned long) ; 
 scalar_t__ IS_SHA1_HMAC (unsigned long) ; 
 scalar_t__ IS_SHA256 (unsigned long) ; 
 scalar_t__ IS_SHA256_HMAC (unsigned long) ; 
 scalar_t__ IS_SHA_HMAC (unsigned long) ; 
 scalar_t__ QCE_MAX_NONCE_WORDS ; 

__attribute__((used)) static u32 qce_auth_cfg(unsigned long flags, u32 key_size)
{
	u32 cfg = 0;

	if (IS_AES(flags) && (IS_CCM(flags) || IS_CMAC(flags)))
		cfg |= AUTH_ALG_AES << AUTH_ALG_SHIFT;
	else
		cfg |= AUTH_ALG_SHA << AUTH_ALG_SHIFT;

	if (IS_CCM(flags) || IS_CMAC(flags)) {
		if (key_size == AES_KEYSIZE_128)
			cfg |= AUTH_KEY_SZ_AES128 << AUTH_KEY_SIZE_SHIFT;
		else if (key_size == AES_KEYSIZE_256)
			cfg |= AUTH_KEY_SZ_AES256 << AUTH_KEY_SIZE_SHIFT;
	}

	if (IS_SHA1(flags) || IS_SHA1_HMAC(flags))
		cfg |= AUTH_SIZE_SHA1 << AUTH_SIZE_SHIFT;
	else if (IS_SHA256(flags) || IS_SHA256_HMAC(flags))
		cfg |= AUTH_SIZE_SHA256 << AUTH_SIZE_SHIFT;
	else if (IS_CMAC(flags))
		cfg |= AUTH_SIZE_ENUM_16_BYTES << AUTH_SIZE_SHIFT;

	if (IS_SHA1(flags) || IS_SHA256(flags))
		cfg |= AUTH_MODE_HASH << AUTH_MODE_SHIFT;
	else if (IS_SHA1_HMAC(flags) || IS_SHA256_HMAC(flags) ||
		 IS_CBC(flags) || IS_CTR(flags))
		cfg |= AUTH_MODE_HMAC << AUTH_MODE_SHIFT;
	else if (IS_AES(flags) && IS_CCM(flags))
		cfg |= AUTH_MODE_CCM << AUTH_MODE_SHIFT;
	else if (IS_AES(flags) && IS_CMAC(flags))
		cfg |= AUTH_MODE_CMAC << AUTH_MODE_SHIFT;

	if (IS_SHA(flags) || IS_SHA_HMAC(flags))
		cfg |= AUTH_POS_BEFORE << AUTH_POS_SHIFT;

	if (IS_CCM(flags))
		cfg |= QCE_MAX_NONCE_WORDS << AUTH_NONCE_NUM_WORDS_SHIFT;

	if (IS_CBC(flags) || IS_CTR(flags) || IS_CCM(flags) ||
	    IS_CMAC(flags))
		cfg |= BIT(AUTH_LAST_SHIFT) | BIT(AUTH_FIRST_SHIFT);

	return cfg;
}