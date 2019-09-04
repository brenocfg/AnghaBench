#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mlx4_mtt {int dummy; } ;
struct mlx4_ib_dev {TYPE_3__* dev; } ;
struct mlx4_ib_cq_buf {struct mlx4_mtt mtt; } ;
struct TYPE_7__ {int cqe; } ;
struct mlx4_ib_cq {int /*<<< orphan*/  resize_mutex; int /*<<< orphan*/ * resize_umem; TYPE_5__* resize_buf; int /*<<< orphan*/  lock; TYPE_2__ ibcq; struct mlx4_ib_cq_buf buf; int /*<<< orphan*/ * umem; int /*<<< orphan*/  mcq; } ;
struct ib_udata {int dummy; } ;
struct ib_cq {int cqe; scalar_t__ uobject; int /*<<< orphan*/  device; } ;
struct TYPE_9__ {int cqe; struct mlx4_ib_cq_buf buf; } ;
struct TYPE_6__ {int max_cqes; } ;
struct TYPE_8__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 int mlx4_alloc_resize_buf (struct mlx4_ib_dev*,struct mlx4_ib_cq*,int) ; 
 int mlx4_alloc_resize_umem (struct mlx4_ib_dev*,struct mlx4_ib_cq*,int,struct ib_udata*) ; 
 int mlx4_cq_resize (TYPE_3__*,int /*<<< orphan*/ *,int,struct mlx4_mtt*) ; 
 int /*<<< orphan*/  mlx4_ib_cq_resize_copy_cqes (struct mlx4_ib_cq*) ; 
 int /*<<< orphan*/  mlx4_ib_free_cq_buf (struct mlx4_ib_dev*,struct mlx4_ib_cq_buf*,int) ; 
 int mlx4_ib_get_outstanding_cqes (struct mlx4_ib_cq*) ; 
 int /*<<< orphan*/  mlx4_mtt_cleanup (TYPE_3__*,struct mlx4_mtt*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct mlx4_ib_cq* to_mcq (struct ib_cq*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

int mlx4_ib_resize_cq(struct ib_cq *ibcq, int entries, struct ib_udata *udata)
{
	struct mlx4_ib_dev *dev = to_mdev(ibcq->device);
	struct mlx4_ib_cq *cq = to_mcq(ibcq);
	struct mlx4_mtt mtt;
	int outst_cqe;
	int err;

	mutex_lock(&cq->resize_mutex);
	if (entries < 1 || entries > dev->dev->caps.max_cqes) {
		err = -EINVAL;
		goto out;
	}

	entries = roundup_pow_of_two(entries + 1);
	if (entries == ibcq->cqe + 1) {
		err = 0;
		goto out;
	}

	if (entries > dev->dev->caps.max_cqes + 1) {
		err = -EINVAL;
		goto out;
	}

	if (ibcq->uobject) {
		err = mlx4_alloc_resize_umem(dev, cq, entries, udata);
		if (err)
			goto out;
	} else {
		/* Can't be smaller than the number of outstanding CQEs */
		outst_cqe = mlx4_ib_get_outstanding_cqes(cq);
		if (entries < outst_cqe + 1) {
			err = -EINVAL;
			goto out;
		}

		err = mlx4_alloc_resize_buf(dev, cq, entries);
		if (err)
			goto out;
	}

	mtt = cq->buf.mtt;

	err = mlx4_cq_resize(dev->dev, &cq->mcq, entries, &cq->resize_buf->buf.mtt);
	if (err)
		goto err_buf;

	mlx4_mtt_cleanup(dev->dev, &mtt);
	if (ibcq->uobject) {
		cq->buf      = cq->resize_buf->buf;
		cq->ibcq.cqe = cq->resize_buf->cqe;
		ib_umem_release(cq->umem);
		cq->umem     = cq->resize_umem;

		kfree(cq->resize_buf);
		cq->resize_buf = NULL;
		cq->resize_umem = NULL;
	} else {
		struct mlx4_ib_cq_buf tmp_buf;
		int tmp_cqe = 0;

		spin_lock_irq(&cq->lock);
		if (cq->resize_buf) {
			mlx4_ib_cq_resize_copy_cqes(cq);
			tmp_buf = cq->buf;
			tmp_cqe = cq->ibcq.cqe;
			cq->buf      = cq->resize_buf->buf;
			cq->ibcq.cqe = cq->resize_buf->cqe;

			kfree(cq->resize_buf);
			cq->resize_buf = NULL;
		}
		spin_unlock_irq(&cq->lock);

		if (tmp_cqe)
			mlx4_ib_free_cq_buf(dev, &tmp_buf, tmp_cqe);
	}

	goto out;

err_buf:
	mlx4_mtt_cleanup(dev->dev, &cq->resize_buf->buf.mtt);
	if (!ibcq->uobject)
		mlx4_ib_free_cq_buf(dev, &cq->resize_buf->buf,
				    cq->resize_buf->cqe);

	kfree(cq->resize_buf);
	cq->resize_buf = NULL;

	if (cq->resize_umem) {
		ib_umem_release(cq->resize_umem);
		cq->resize_umem = NULL;
	}

out:
	mutex_unlock(&cq->resize_mutex);

	return err;
}