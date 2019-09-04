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
struct pblk_c_ctx {int /*<<< orphan*/  list; } ;
struct pblk {int dummy; } ;
struct nvm_rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 unsigned long pblk_end_w_bio (struct pblk*,struct nvm_rq*,struct pblk_c_ctx*) ; 

__attribute__((used)) static unsigned long pblk_end_queued_w_bio(struct pblk *pblk,
					   struct nvm_rq *rqd,
					   struct pblk_c_ctx *c_ctx)
{
	list_del(&c_ctx->list);
	return pblk_end_w_bio(pblk, rqd, c_ctx);
}