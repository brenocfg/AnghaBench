#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mlx4_en_priv {struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {TYPE_6__* dev; } ;
struct TYPE_11__ {scalar_t__ buf; } ;
struct TYPE_12__ {TYPE_4__ direct; } ;
struct TYPE_14__ {TYPE_5__ buf; } ;
struct mlx4_en_cq {int size; int buf_size; int ring; int type; TYPE_7__ wqres; struct mlx4_cqe* buf; int /*<<< orphan*/  vector; } ;
struct mlx4_cqe {int dummy; } ;
typedef  enum cq_type { ____Placeholder_cq_type } cq_type ;
struct TYPE_8__ {int cqe_size; int /*<<< orphan*/  num_comp_vectors; } ;
struct TYPE_13__ {int numa_node; TYPE_3__* persist; TYPE_1__ caps; } ;
struct TYPE_10__ {TYPE_2__* pdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_cq*) ; 
 struct mlx4_en_cq* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int mlx4_alloc_hwq_res (TYPE_6__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  set_dev_node (int /*<<< orphan*/ *,int) ; 

int mlx4_en_create_cq(struct mlx4_en_priv *priv,
		      struct mlx4_en_cq **pcq,
		      int entries, int ring, enum cq_type mode,
		      int node)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_cq *cq;
	int err;

	cq = kzalloc_node(sizeof(*cq), GFP_KERNEL, node);
	if (!cq) {
		en_err(priv, "Failed to allocate CQ structure\n");
		return -ENOMEM;
	}

	cq->size = entries;
	cq->buf_size = cq->size * mdev->dev->caps.cqe_size;

	cq->ring = ring;
	cq->type = mode;
	cq->vector = mdev->dev->caps.num_comp_vectors;

	/* Allocate HW buffers on provided NUMA node.
	 * dev->numa_node is used in mtt range allocation flow.
	 */
	set_dev_node(&mdev->dev->persist->pdev->dev, node);
	err = mlx4_alloc_hwq_res(mdev->dev, &cq->wqres,
				cq->buf_size);
	set_dev_node(&mdev->dev->persist->pdev->dev, mdev->dev->numa_node);
	if (err)
		goto err_cq;

	cq->buf = (struct mlx4_cqe *)cq->wqres.buf.direct.buf;
	*pcq = cq;

	return 0;

err_cq:
	kfree(cq);
	*pcq = NULL;
	return err;
}