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
struct skcipher_request {int dummy; } ;
struct rctx {scalar_t__ ext; scalar_t__ left; } ;

/* Variables and functions */
 int /*<<< orphan*/  kzfree (scalar_t__) ; 
 struct rctx* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static void exit_crypt(struct skcipher_request *req)
{
	struct rctx *rctx = skcipher_request_ctx(req);

	rctx->left = 0;

	if (rctx->ext)
		kzfree(rctx->ext);
}