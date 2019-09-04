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
struct crypto_ahash {int dummy; } ;
struct ahash_request {int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MD5_DIGEST_SIZE 130 
#define  SHA1_DIGEST_SIZE 129 
#define  SHA256_DIGEST_SIZE 128 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  md5_zero_message_hash ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sha1_zero_message_hash ; 
 int /*<<< orphan*/  sha256_zero_message_hash ; 

__attribute__((used)) static int zero_message_process(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	int rk_digest_size = crypto_ahash_digestsize(tfm);

	switch (rk_digest_size) {
	case SHA1_DIGEST_SIZE:
		memcpy(req->result, sha1_zero_message_hash, rk_digest_size);
		break;
	case SHA256_DIGEST_SIZE:
		memcpy(req->result, sha256_zero_message_hash, rk_digest_size);
		break;
	case MD5_DIGEST_SIZE:
		memcpy(req->result, md5_zero_message_hash, rk_digest_size);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}