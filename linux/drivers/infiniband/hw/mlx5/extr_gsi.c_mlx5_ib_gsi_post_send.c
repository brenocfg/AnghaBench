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
struct TYPE_3__ {int max_send_wr; } ;
struct mlx5_ib_gsi_qp {int outstanding_pi; int /*<<< orphan*/  lock; TYPE_1__ cap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * next; } ;
struct ib_ud_wr {TYPE_2__ wr; } ;
struct ib_send_wr {struct ib_send_wr* next; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 struct ib_qp* get_tx_qp (struct mlx5_ib_gsi_qp*,struct ib_ud_wr*) ; 
 struct mlx5_ib_gsi_qp* gsi_qp (struct ib_qp*) ; 
 int ib_post_send (struct ib_qp*,TYPE_2__*,struct ib_send_wr const**) ; 
 int mlx5_ib_add_outstanding_wr (struct mlx5_ib_gsi_qp*,struct ib_ud_wr*,int /*<<< orphan*/ *) ; 
 int mlx5_ib_gsi_silent_drop (struct mlx5_ib_gsi_qp*,struct ib_ud_wr*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ib_ud_wr* ud_wr (struct ib_send_wr const*) ; 

int mlx5_ib_gsi_post_send(struct ib_qp *qp, const struct ib_send_wr *wr,
			  const struct ib_send_wr **bad_wr)
{
	struct mlx5_ib_gsi_qp *gsi = gsi_qp(qp);
	struct ib_qp *tx_qp;
	unsigned long flags;
	int ret;

	for (; wr; wr = wr->next) {
		struct ib_ud_wr cur_wr = *ud_wr(wr);

		cur_wr.wr.next = NULL;

		spin_lock_irqsave(&gsi->lock, flags);
		tx_qp = get_tx_qp(gsi, &cur_wr);
		if (!tx_qp) {
			ret = mlx5_ib_gsi_silent_drop(gsi, &cur_wr);
			if (ret)
				goto err;
			spin_unlock_irqrestore(&gsi->lock, flags);
			continue;
		}

		ret = mlx5_ib_add_outstanding_wr(gsi, &cur_wr, NULL);
		if (ret)
			goto err;

		ret = ib_post_send(tx_qp, &cur_wr.wr, bad_wr);
		if (ret) {
			/* Undo the effect of adding the outstanding wr */
			gsi->outstanding_pi = (gsi->outstanding_pi - 1) %
					      gsi->cap.max_send_wr;
			goto err;
		}
		spin_unlock_irqrestore(&gsi->lock, flags);
	}

	return 0;

err:
	spin_unlock_irqrestore(&gsi->lock, flags);
	*bad_wr = wr;
	return ret;
}