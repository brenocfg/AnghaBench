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
struct pblk {int /*<<< orphan*/  e_rq_pool; int /*<<< orphan*/  r_rq_pool; int /*<<< orphan*/  w_rq_pool; } ;
struct nvm_rq {int dummy; } ;
typedef  int /*<<< orphan*/  mempool_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  PBLK_READ 130 
#define  PBLK_WRITE 129 
#define  PBLK_WRITE_INT 128 
 struct nvm_rq* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvm_rq*,int /*<<< orphan*/ ,int) ; 
 int pblk_g_rq_size ; 
 int pblk_w_rq_size ; 

struct nvm_rq *pblk_alloc_rqd(struct pblk *pblk, int type)
{
	mempool_t *pool;
	struct nvm_rq *rqd;
	int rq_size;

	switch (type) {
	case PBLK_WRITE:
	case PBLK_WRITE_INT:
		pool = &pblk->w_rq_pool;
		rq_size = pblk_w_rq_size;
		break;
	case PBLK_READ:
		pool = &pblk->r_rq_pool;
		rq_size = pblk_g_rq_size;
		break;
	default:
		pool = &pblk->e_rq_pool;
		rq_size = pblk_g_rq_size;
	}

	rqd = mempool_alloc(pool, GFP_KERNEL);
	memset(rqd, 0, rq_size);

	return rqd;
}