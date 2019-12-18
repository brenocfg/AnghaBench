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
typedef  scalar_t__ u32 ;
struct qman_fq {int /*<<< orphan*/  fqid; } ;
struct qm_mcr_queryfq_np {int state; } ;
struct qm_fqd {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  QM_FQID_RANGE_START ; 
 int QM_MCR_NP_STATE_MASK ; 
 int QM_MCR_NP_STATE_OOS ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ qm_fqd_get_chan (struct qm_fqd*) ; 
 int qman_query_fq (struct qman_fq*,struct qm_fqd*) ; 
 int qman_query_fq_np (struct qman_fq*,struct qm_mcr_queryfq_np*) ; 
 int qman_shutdown_fq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qpool_cleanup(u32 qp)
{
	/*
	 * We query all FQDs starting from
	 * FQID 1 until we get an "invalid FQID" error, looking for non-OOS FQDs
	 * whose destination channel is the pool-channel being released.
	 * When a non-OOS FQD is found we attempt to clean it up
	 */
	struct qman_fq fq = {
		.fqid = QM_FQID_RANGE_START
	};
	int err;

	do {
		struct qm_mcr_queryfq_np np;

		err = qman_query_fq_np(&fq, &np);
		if (err == -ERANGE)
			/* FQID range exceeded, found no problems */
			return 0;
		else if (WARN_ON(err))
			return err;

		if ((np.state & QM_MCR_NP_STATE_MASK) != QM_MCR_NP_STATE_OOS) {
			struct qm_fqd fqd;

			err = qman_query_fq(&fq, &fqd);
			if (WARN_ON(err))
				return err;
			if (qm_fqd_get_chan(&fqd) == qp) {
				/* The channel is the FQ's target, clean it */
				err = qman_shutdown_fq(fq.fqid);
				if (err)
					/*
					 * Couldn't shut down the FQ
					 * so the pool must be leaked
					 */
					return err;
			}
		}
		/* Move to the next FQID */
		fq.fqid++;
	} while (1);
}