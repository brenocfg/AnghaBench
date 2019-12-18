#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct fc_lport {int dummy; } ;
struct fc_exch_pool {scalar_t__ left; scalar_t__ right; int next_index; int /*<<< orphan*/  lock; int /*<<< orphan*/  total_exches; int /*<<< orphan*/  ex_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  no_free_exch_xid; int /*<<< orphan*/  no_free_exch; } ;
struct fc_exch_mgr {int pool_max_index; int /*<<< orphan*/  ep_pool; TYPE_1__ stats; int /*<<< orphan*/  class; scalar_t__ min_xid; int /*<<< orphan*/  pool; } ;
struct fc_exch {int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  resp_wq; scalar_t__ resp_active; int /*<<< orphan*/  class; scalar_t__ rxid; int /*<<< orphan*/  f_ctl; struct fc_lport* lp; struct fc_exch_pool* pool; struct fc_exch_mgr* em; scalar_t__ xid; scalar_t__ oxid; int /*<<< orphan*/  seq_id; int /*<<< orphan*/  ex_list; int /*<<< orphan*/  ex_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_FC_FIRST_SEQ ; 
 scalar_t__ FC_XID_UNKNOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int fc_cpu_order ; 
 int /*<<< orphan*/  fc_exch_hold (struct fc_exch*) ; 
 scalar_t__ fc_exch_ptr_get (struct fc_exch_pool*,int) ; 
 int /*<<< orphan*/  fc_exch_ptr_set (struct fc_exch_pool*,int,struct fc_exch*) ; 
 int /*<<< orphan*/  fc_exch_timeout ; 
 int /*<<< orphan*/  fc_seq_alloc (struct fc_exch*,int /*<<< orphan*/ ) ; 
 unsigned int get_cpu () ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct fc_exch* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct fc_exch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_exch*,int /*<<< orphan*/ ,int) ; 
 struct fc_exch_pool* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fc_exch *fc_exch_em_alloc(struct fc_lport *lport,
					struct fc_exch_mgr *mp)
{
	struct fc_exch *ep;
	unsigned int cpu;
	u16 index;
	struct fc_exch_pool *pool;

	/* allocate memory for exchange */
	ep = mempool_alloc(mp->ep_pool, GFP_ATOMIC);
	if (!ep) {
		atomic_inc(&mp->stats.no_free_exch);
		goto out;
	}
	memset(ep, 0, sizeof(*ep));

	cpu = get_cpu();
	pool = per_cpu_ptr(mp->pool, cpu);
	spin_lock_bh(&pool->lock);
	put_cpu();

	/* peek cache of free slot */
	if (pool->left != FC_XID_UNKNOWN) {
		if (!WARN_ON(fc_exch_ptr_get(pool, pool->left))) {
			index = pool->left;
			pool->left = FC_XID_UNKNOWN;
			goto hit;
		}
	}
	if (pool->right != FC_XID_UNKNOWN) {
		if (!WARN_ON(fc_exch_ptr_get(pool, pool->right))) {
			index = pool->right;
			pool->right = FC_XID_UNKNOWN;
			goto hit;
		}
	}

	index = pool->next_index;
	/* allocate new exch from pool */
	while (fc_exch_ptr_get(pool, index)) {
		index = index == mp->pool_max_index ? 0 : index + 1;
		if (index == pool->next_index)
			goto err;
	}
	pool->next_index = index == mp->pool_max_index ? 0 : index + 1;
hit:
	fc_exch_hold(ep);	/* hold for exch in mp */
	spin_lock_init(&ep->ex_lock);
	/*
	 * Hold exch lock for caller to prevent fc_exch_reset()
	 * from releasing exch	while fc_exch_alloc() caller is
	 * still working on exch.
	 */
	spin_lock_bh(&ep->ex_lock);

	fc_exch_ptr_set(pool, index, ep);
	list_add_tail(&ep->ex_list, &pool->ex_list);
	fc_seq_alloc(ep, ep->seq_id++);
	pool->total_exches++;
	spin_unlock_bh(&pool->lock);

	/*
	 *  update exchange
	 */
	ep->oxid = ep->xid = (index << fc_cpu_order | cpu) + mp->min_xid;
	ep->em = mp;
	ep->pool = pool;
	ep->lp = lport;
	ep->f_ctl = FC_FC_FIRST_SEQ;	/* next seq is first seq */
	ep->rxid = FC_XID_UNKNOWN;
	ep->class = mp->class;
	ep->resp_active = 0;
	init_waitqueue_head(&ep->resp_wq);
	INIT_DELAYED_WORK(&ep->timeout_work, fc_exch_timeout);
out:
	return ep;
err:
	spin_unlock_bh(&pool->lock);
	atomic_inc(&mp->stats.no_free_exch_xid);
	mempool_free(ep, mp->ep_pool);
	return NULL;
}