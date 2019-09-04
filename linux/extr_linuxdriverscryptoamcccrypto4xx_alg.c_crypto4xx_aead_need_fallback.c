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
struct crypto_aead {int authsize; } ;
struct aead_request {int assoclen; int* iv; } ;

/* Variables and functions */
 unsigned int AES_BLOCK_SIZE ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 

__attribute__((used)) static inline bool crypto4xx_aead_need_fallback(struct aead_request *req,
						unsigned int len,
						bool is_ccm, bool decrypt)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);

	/* authsize has to be a multiple of 4 */
	if (aead->authsize & 3)
		return true;

	/*
	 * hardware does not handle cases where plaintext
	 * is less than a block.
	 */
	if (len < AES_BLOCK_SIZE)
		return true;

	/* assoc len needs to be a multiple of 4 and <= 1020 */
	if (req->assoclen & 0x3 || req->assoclen > 1020)
		return true;

	/* CCM supports only counter field length of 2 and 4 bytes */
	if (is_ccm && !(req->iv[0] == 1 || req->iv[0] == 3))
		return true;

	return false;
}