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
struct page {int dummy; } ;
struct ahash_request {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  crypto_ahash_update (struct ahash_request*) ; 
 int /*<<< orphan*/  sg_init_marker (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nvme_tcp_ddgst_update(struct ahash_request *hash,
		struct page *page, off_t off, size_t len)
{
	struct scatterlist sg;

	sg_init_marker(&sg, 1);
	sg_set_page(&sg, page, len, off);
	ahash_request_set_crypt(hash, &sg, NULL, len);
	crypto_ahash_update(hash);
}