#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct mlx4_ib_dev {TYPE_2__* dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  page_shift; int /*<<< orphan*/  npages; } ;
struct mlx4_ib_cq_buf {int entry_size; TYPE_5__ buf; int /*<<< orphan*/  mtt; } ;
struct TYPE_10__ {int cqe_size; } ;
struct TYPE_11__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int mlx4_buf_alloc (TYPE_2__*,int,int,TYPE_5__*) ; 
 int /*<<< orphan*/  mlx4_buf_free (TYPE_2__*,int,TYPE_5__*) ; 
 int mlx4_buf_write_mtt (TYPE_2__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  mlx4_mtt_cleanup (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int mlx4_mtt_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx4_ib_alloc_cq_buf(struct mlx4_ib_dev *dev, struct mlx4_ib_cq_buf *buf, int nent)
{
	int err;

	err = mlx4_buf_alloc(dev->dev, nent * dev->dev->caps.cqe_size,
			     PAGE_SIZE * 2, &buf->buf);

	if (err)
		goto out;

	buf->entry_size = dev->dev->caps.cqe_size;
	err = mlx4_mtt_init(dev->dev, buf->buf.npages, buf->buf.page_shift,
				    &buf->mtt);
	if (err)
		goto err_buf;

	err = mlx4_buf_write_mtt(dev->dev, &buf->mtt, &buf->buf);
	if (err)
		goto err_mtt;

	return 0;

err_mtt:
	mlx4_mtt_cleanup(dev->dev, &buf->mtt);

err_buf:
	mlx4_buf_free(dev->dev, nent * buf->entry_size, &buf->buf);

out:
	return err;
}