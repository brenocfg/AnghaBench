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
struct scatterlist {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,void*,size_t) ; 
 int /*<<< orphan*/  crypto_ahash_digest (struct ahash_request*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void*,size_t) ; 

__attribute__((used)) static inline void nvme_tcp_hdgst(struct ahash_request *hash,
		void *pdu, size_t len)
{
	struct scatterlist sg;

	sg_init_one(&sg, pdu, len);
	ahash_request_set_crypt(hash, &sg, pdu + len, len);
	crypto_ahash_digest(hash);
}