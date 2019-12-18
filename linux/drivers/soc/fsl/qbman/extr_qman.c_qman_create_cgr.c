#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qman_portal {int /*<<< orphan*/  cgr_lock; int /*<<< orphan*/ * cgrs; TYPE_1__* config; int /*<<< orphan*/  cgr_cbs; } ;
struct qman_cgr {size_t cgrid; int /*<<< orphan*/  (* cb ) (struct qman_portal*,struct qman_cgr*,int) ;int /*<<< orphan*/  node; int /*<<< orphan*/  chan; } ;
struct TYPE_4__ {scalar_t__ cscn_en; int /*<<< orphan*/  cscn_targ; } ;
struct qm_mcr_querycgr {TYPE_2__ cgr; } ;
struct qm_mcc_initcgr {int /*<<< orphan*/  we_mask; int /*<<< orphan*/  cgr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 size_t CGR_NUM ; 
 int EINVAL ; 
 int /*<<< orphan*/  PORTAL_IDX (struct qman_portal*) ; 
 int QMAN_CGR_FLAG_USE_INIT ; 
 int /*<<< orphan*/  QM_CGR_WE_CSCN_TARG ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct qman_portal* get_affine_portal () ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  put_affine_portal () ; 
 int /*<<< orphan*/  qm_cgr_cscn_targ_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qm_modify_cgr (struct qman_cgr*,int,struct qm_mcc_initcgr*) ; 
 int /*<<< orphan*/ * qman_cgr_cpus ; 
 scalar_t__ qman_cgrs_get (int /*<<< orphan*/ *,size_t) ; 
 int qman_query_cgr (struct qman_cgr*,struct qm_mcr_querycgr*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct qman_portal*,struct qman_cgr*,int) ; 

int qman_create_cgr(struct qman_cgr *cgr, u32 flags,
		    struct qm_mcc_initcgr *opts)
{
	struct qm_mcr_querycgr cgr_state;
	int ret;
	struct qman_portal *p;

	/*
	 * We have to check that the provided CGRID is within the limits of the
	 * data-structures, for obvious reasons. However we'll let h/w take
	 * care of determining whether it's within the limits of what exists on
	 * the SoC.
	 */
	if (cgr->cgrid >= CGR_NUM)
		return -EINVAL;

	preempt_disable();
	p = get_affine_portal();
	qman_cgr_cpus[cgr->cgrid] = smp_processor_id();
	preempt_enable();

	cgr->chan = p->config->channel;
	spin_lock(&p->cgr_lock);

	if (opts) {
		struct qm_mcc_initcgr local_opts = *opts;

		ret = qman_query_cgr(cgr, &cgr_state);
		if (ret)
			goto out;

		qm_cgr_cscn_targ_set(&local_opts.cgr, PORTAL_IDX(p),
				     be32_to_cpu(cgr_state.cgr.cscn_targ));
		local_opts.we_mask |= cpu_to_be16(QM_CGR_WE_CSCN_TARG);

		/* send init if flags indicate so */
		if (flags & QMAN_CGR_FLAG_USE_INIT)
			ret = qm_modify_cgr(cgr, QMAN_CGR_FLAG_USE_INIT,
					    &local_opts);
		else
			ret = qm_modify_cgr(cgr, 0, &local_opts);
		if (ret)
			goto out;
	}

	list_add(&cgr->node, &p->cgr_cbs);

	/* Determine if newly added object requires its callback to be called */
	ret = qman_query_cgr(cgr, &cgr_state);
	if (ret) {
		/* we can't go back, so proceed and return success */
		dev_err(p->config->dev, "CGR HW state partially modified\n");
		ret = 0;
		goto out;
	}
	if (cgr->cb && cgr_state.cgr.cscn_en &&
	    qman_cgrs_get(&p->cgrs[1], cgr->cgrid))
		cgr->cb(p, cgr, 1);
out:
	spin_unlock(&p->cgr_lock);
	put_affine_portal();
	return ret;
}