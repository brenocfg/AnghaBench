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
struct nvme_tcp_queue {void* snd_hash; void* rcv_hash; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_ahash*) ; 
 int PTR_ERR (struct crypto_ahash*) ; 
 void* ahash_request_alloc (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_request_free (void*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct crypto_ahash* crypto_alloc_ahash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_ahash (struct crypto_ahash*) ; 

__attribute__((used)) static int nvme_tcp_alloc_crypto(struct nvme_tcp_queue *queue)
{
	struct crypto_ahash *tfm;

	tfm = crypto_alloc_ahash("crc32c", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(tfm))
		return PTR_ERR(tfm);

	queue->snd_hash = ahash_request_alloc(tfm, GFP_KERNEL);
	if (!queue->snd_hash)
		goto free_tfm;
	ahash_request_set_callback(queue->snd_hash, 0, NULL, NULL);

	queue->rcv_hash = ahash_request_alloc(tfm, GFP_KERNEL);
	if (!queue->rcv_hash)
		goto free_snd_hash;
	ahash_request_set_callback(queue->rcv_hash, 0, NULL, NULL);

	return 0;
free_snd_hash:
	ahash_request_free(queue->snd_hash);
free_tfm:
	crypto_free_ahash(tfm);
	return -ENOMEM;
}