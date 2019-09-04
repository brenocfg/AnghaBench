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
struct sha512_hash_ctx {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct sha512_hash_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (struct sha512_hash_ctx*,void const*,int) ; 

__attribute__((used)) static int sha512_mb_import(struct ahash_request *areq, const void *in)
{
	struct sha512_hash_ctx *sctx = ahash_request_ctx(areq);

	memcpy(sctx, in, sizeof(*sctx));

	return 0;
}