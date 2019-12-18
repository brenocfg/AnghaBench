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
struct nvme_tcp_queue {int /*<<< orphan*/  snd_hash; int /*<<< orphan*/  rcv_hash; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_request_free (int /*<<< orphan*/ ) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_ahash (struct crypto_ahash*) ; 

__attribute__((used)) static void nvme_tcp_free_crypto(struct nvme_tcp_queue *queue)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(queue->rcv_hash);

	ahash_request_free(queue->rcv_hash);
	ahash_request_free(queue->snd_hash);
	crypto_free_ahash(tfm);
}