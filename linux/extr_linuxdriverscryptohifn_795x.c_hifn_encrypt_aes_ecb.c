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
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACRYPTO_MODE_ECB ; 
 int /*<<< orphan*/  ACRYPTO_OP_ENCRYPT ; 
 int /*<<< orphan*/  ACRYPTO_TYPE_AES_128 ; 
 int hifn_setup_crypto (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hifn_encrypt_aes_ecb(struct ablkcipher_request *req)
{
	return hifn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_AES_128, ACRYPTO_MODE_ECB);
}