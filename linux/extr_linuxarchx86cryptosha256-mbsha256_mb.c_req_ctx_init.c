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
struct mcryptd_hash_request_ctx {int /*<<< orphan*/  flag; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_UPDATE ; 

__attribute__((used)) static void req_ctx_init(struct mcryptd_hash_request_ctx *rctx,
				struct ahash_request *areq)
{
	rctx->flag = HASH_UPDATE;
}