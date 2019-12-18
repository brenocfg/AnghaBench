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
struct pblk_g_ctx {scalar_t__ private; } ;
struct pblk {int dummy; } ;
struct nvm_rq {int /*<<< orphan*/  error; struct pblk* private; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pblk_end_io_read (struct pblk*,struct nvm_rq*,int) ; 
 struct pblk_g_ctx* nvm_rq_to_pdu (struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_end_user_read (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pblk_end_io_read(struct nvm_rq *rqd)
{
	struct pblk *pblk = rqd->private;
	struct pblk_g_ctx *r_ctx = nvm_rq_to_pdu(rqd);
	struct bio *bio = (struct bio *)r_ctx->private;

	pblk_end_user_read(bio, rqd->error);
	__pblk_end_io_read(pblk, rqd, true);
}