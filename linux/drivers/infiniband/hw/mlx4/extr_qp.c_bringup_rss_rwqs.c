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
typedef  scalar_t__ u8 ;
struct mlx4_ib_qp {scalar_t__ rss_usecnt; scalar_t__ port; int /*<<< orphan*/  mutex; } ;
struct ib_wq {scalar_t__ state; int /*<<< orphan*/  wq_num; } ;
struct ib_udata {int dummy; } ;
struct ib_rwq_ind_table {int log_ind_tbl_size; struct ib_wq** ind_tbl; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_WQS_RDY ; 
 scalar_t__ IB_WQS_RESET ; 
 int _mlx4_ib_modify_wq (struct ib_wq*,scalar_t__,struct ib_udata*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 struct mlx4_ib_qp* to_mqp (struct ib_qp*) ; 

__attribute__((used)) static int bringup_rss_rwqs(struct ib_rwq_ind_table *ind_tbl, u8 port_num,
			    struct ib_udata *udata)
{
	int err = 0;
	int i;

	for (i = 0; i < (1 << ind_tbl->log_ind_tbl_size); i++) {
		struct ib_wq *ibwq = ind_tbl->ind_tbl[i];
		struct mlx4_ib_qp *wq = to_mqp((struct ib_qp *)ibwq);

		mutex_lock(&wq->mutex);

		/* Mlx4_ib restrictions:
		 * WQ's is associated to a port according to the RSS QP it is
		 * associates to.
		 * In case the WQ is associated to a different port by another
		 * RSS QP, return a failure.
		 */
		if ((wq->rss_usecnt > 0) && (wq->port != port_num)) {
			err = -EINVAL;
			mutex_unlock(&wq->mutex);
			break;
		}
		wq->port = port_num;
		if ((wq->rss_usecnt == 0) && (ibwq->state == IB_WQS_RDY)) {
			err = _mlx4_ib_modify_wq(ibwq, IB_WQS_RDY, udata);
			if (err) {
				mutex_unlock(&wq->mutex);
				break;
			}
		}
		wq->rss_usecnt++;

		mutex_unlock(&wq->mutex);
	}

	if (i && err) {
		int j;

		for (j = (i - 1); j >= 0; j--) {
			struct ib_wq *ibwq = ind_tbl->ind_tbl[j];
			struct mlx4_ib_qp *wq = to_mqp((struct ib_qp *)ibwq);

			mutex_lock(&wq->mutex);

			if ((wq->rss_usecnt == 1) &&
			    (ibwq->state == IB_WQS_RDY))
				if (_mlx4_ib_modify_wq(ibwq, IB_WQS_RESET,
						       udata))
					pr_warn("failed to reverse WQN=0x%06x\n",
						ibwq->wq_num);
			wq->rss_usecnt--;

			mutex_unlock(&wq->mutex);
		}
	}

	return err;
}