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
struct rvt_qp {struct hfi1_qp_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lock; int /*<<< orphan*/  list; } ;
struct hfi1_qp_priv {TYPE_1__ s_iowait; } ;
typedef  int /*<<< orphan*/  seqlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_put_qp (struct rvt_qp*) ; 
 int /*<<< orphan*/  write_seqlock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_sequnlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void flush_iowait(struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;
	unsigned long flags;
	seqlock_t *lock = priv->s_iowait.lock;

	if (!lock)
		return;
	write_seqlock_irqsave(lock, flags);
	if (!list_empty(&priv->s_iowait.list)) {
		list_del_init(&priv->s_iowait.list);
		priv->s_iowait.lock = NULL;
		rvt_put_qp(qp);
	}
	write_sequnlock_irqrestore(lock, flags);
}