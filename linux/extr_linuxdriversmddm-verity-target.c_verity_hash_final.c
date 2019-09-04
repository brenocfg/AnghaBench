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
typedef  int /*<<< orphan*/  u8 ;
struct dm_verity {scalar_t__ salt_size; int /*<<< orphan*/  salt; int /*<<< orphan*/  version; } ;
struct crypto_wait {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_final (struct ahash_request*) ; 
 int crypto_wait_req (int /*<<< orphan*/ ,struct crypto_wait*) ; 
 scalar_t__ unlikely (int) ; 
 int verity_hash_update (struct dm_verity*,struct ahash_request*,int /*<<< orphan*/ ,scalar_t__,struct crypto_wait*) ; 

__attribute__((used)) static int verity_hash_final(struct dm_verity *v, struct ahash_request *req,
			     u8 *digest, struct crypto_wait *wait)
{
	int r;

	if (unlikely(v->salt_size && (!v->version))) {
		r = verity_hash_update(v, req, v->salt, v->salt_size, wait);

		if (r < 0) {
			DMERR("verity_hash_final failed updating salt: %d", r);
			goto out;
		}
	}

	ahash_request_set_crypt(req, NULL, digest, 0);
	r = crypto_wait_req(crypto_ahash_final(req), wait);
out:
	return r;
}