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
union bm_mc_result {int verb; int /*<<< orphan*/ * bufs; } ;
typedef  int u8 ;
struct bman_portal {int /*<<< orphan*/  p; } ;
struct bman_pool {int /*<<< orphan*/  bpid; } ;
struct bm_mc_command {int /*<<< orphan*/  bpid; } ;
struct bm_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  bufs ;

/* Variables and functions */
 int BM_MCC_VERB_ACQUIRE_BUFCOUNT ; 
 int BM_MCC_VERB_CMD_ACQUIRE ; 
 int BM_MCR_VERB_ACQUIRE_BUFCOUNT ; 
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  bm_mc_commit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bm_mc_result_timeout (int /*<<< orphan*/ *,union bm_mc_result**) ; 
 struct bm_mc_command* bm_mc_start (int /*<<< orphan*/ *) ; 
 struct bman_portal* get_affine_portal () ; 
 int /*<<< orphan*/  memcpy (struct bm_buffer*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  put_affine_portal () ; 

int bman_acquire(struct bman_pool *pool, struct bm_buffer *bufs, u8 num)
{
	struct bman_portal *p = get_affine_portal();
	struct bm_mc_command *mcc;
	union bm_mc_result *mcr;
	int ret;

	DPAA_ASSERT(num > 0 && num <= 8);

	mcc = bm_mc_start(&p->p);
	mcc->bpid = pool->bpid;
	bm_mc_commit(&p->p, BM_MCC_VERB_CMD_ACQUIRE |
		     (num & BM_MCC_VERB_ACQUIRE_BUFCOUNT));
	if (!bm_mc_result_timeout(&p->p, &mcr)) {
		put_affine_portal();
		pr_crit("BMan Acquire Timeout\n");
		return -ETIMEDOUT;
	}
	ret = mcr->verb & BM_MCR_VERB_ACQUIRE_BUFCOUNT;
	if (bufs)
		memcpy(&bufs[0], &mcr->bufs[0], num * sizeof(bufs[0]));

	put_affine_portal();
	if (ret != num)
		ret = -ENOMEM;
	return ret;
}