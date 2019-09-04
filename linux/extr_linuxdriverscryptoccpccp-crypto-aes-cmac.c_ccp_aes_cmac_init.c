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
struct ccp_aes_cmac_req_ctx {int null_msg; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct ccp_aes_cmac_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memset (struct ccp_aes_cmac_req_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccp_aes_cmac_init(struct ahash_request *req)
{
	struct ccp_aes_cmac_req_ctx *rctx = ahash_request_ctx(req);

	memset(rctx, 0, sizeof(*rctx));

	rctx->null_msg = 1;

	return 0;
}