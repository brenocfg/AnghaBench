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
struct talitos_ahash_req_ctx {int swinit; scalar_t__* hw_context; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ SHA224_H0 ; 
 scalar_t__ SHA224_H1 ; 
 scalar_t__ SHA224_H2 ; 
 scalar_t__ SHA224_H3 ; 
 scalar_t__ SHA224_H4 ; 
 scalar_t__ SHA224_H5 ; 
 scalar_t__ SHA224_H6 ; 
 scalar_t__ SHA224_H7 ; 
 int /*<<< orphan*/  ahash_init (struct ahash_request*) ; 
 struct talitos_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 

__attribute__((used)) static int ahash_init_sha224_swinit(struct ahash_request *areq)
{
	struct talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);

	req_ctx->hw_context[0] = SHA224_H0;
	req_ctx->hw_context[1] = SHA224_H1;
	req_ctx->hw_context[2] = SHA224_H2;
	req_ctx->hw_context[3] = SHA224_H3;
	req_ctx->hw_context[4] = SHA224_H4;
	req_ctx->hw_context[5] = SHA224_H5;
	req_ctx->hw_context[6] = SHA224_H6;
	req_ctx->hw_context[7] = SHA224_H7;

	/* init 64-bit count */
	req_ctx->hw_context[8] = 0;
	req_ctx->hw_context[9] = 0;

	ahash_init(areq);
	req_ctx->swinit = 1;/* prevent h/w initting context with sha256 values*/

	return 0;
}