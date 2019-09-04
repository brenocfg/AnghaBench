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
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct crypto_shash* ERR_PTR (int /*<<< orphan*/ ) ; 
#define  SHA1_DIGEST_SIZE 132 
#define  SHA224_DIGEST_SIZE 131 
#define  SHA256_DIGEST_SIZE 130 
#define  SHA384_DIGEST_SIZE 129 
#define  SHA512_DIGEST_SIZE 128 
 struct crypto_shash* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct crypto_shash *chcr_alloc_shash(unsigned int ds)
{
	struct crypto_shash *base_hash = ERR_PTR(-EINVAL);

	switch (ds) {
	case SHA1_DIGEST_SIZE:
		base_hash = crypto_alloc_shash("sha1", 0, 0);
		break;
	case SHA224_DIGEST_SIZE:
		base_hash = crypto_alloc_shash("sha224", 0, 0);
		break;
	case SHA256_DIGEST_SIZE:
		base_hash = crypto_alloc_shash("sha256", 0, 0);
		break;
	case SHA384_DIGEST_SIZE:
		base_hash = crypto_alloc_shash("sha384", 0, 0);
		break;
	case SHA512_DIGEST_SIZE:
		base_hash = crypto_alloc_shash("sha512", 0, 0);
		break;
	}

	return base_hash;
}