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
struct shash_desc {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct ahash_request* ahash_request_ctx (struct ahash_request*) ; 
 struct shash_desc* cryptd_shash_desc (struct ahash_request*) ; 
 int crypto_shash_export (struct shash_desc*,void*) ; 

__attribute__((used)) static int ghash_async_export(struct ahash_request *req, void *out)
{
	struct ahash_request *cryptd_req = ahash_request_ctx(req);
	struct shash_desc *desc = cryptd_shash_desc(cryptd_req);

	return crypto_shash_export(desc, out);
}