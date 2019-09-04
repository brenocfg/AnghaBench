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
struct sha1_hash_ctx {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct sha1_hash_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (void*,struct sha1_hash_ctx*,int) ; 

__attribute__((used)) static int sha1_mb_export(struct ahash_request *areq, void *out)
{
	struct sha1_hash_ctx *sctx = ahash_request_ctx(areq);

	memcpy(out, sctx, sizeof(*sctx));

	return 0;
}