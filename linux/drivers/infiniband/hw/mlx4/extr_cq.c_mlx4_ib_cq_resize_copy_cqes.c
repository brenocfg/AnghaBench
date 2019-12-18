#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int cons_index; } ;
struct TYPE_7__ {int cqe; } ;
struct TYPE_5__ {int entry_size; } ;
struct mlx4_ib_cq {TYPE_4__ mcq; TYPE_3__ ibcq; TYPE_2__* resize_buf; TYPE_1__ buf; } ;
struct mlx4_cqe {int owner_sr_opcode; } ;
struct TYPE_6__ {int cqe; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int MLX4_CQE_OPCODE_MASK ; 
 int MLX4_CQE_OPCODE_RESIZE ; 
 int MLX4_CQE_OWNER_MASK ; 
 struct mlx4_cqe* get_cqe (struct mlx4_ib_cq*,int) ; 
 struct mlx4_cqe* get_cqe_from_buf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (struct mlx4_cqe*,struct mlx4_cqe*,int) ; 

__attribute__((used)) static void mlx4_ib_cq_resize_copy_cqes(struct mlx4_ib_cq *cq)
{
	struct mlx4_cqe *cqe, *new_cqe;
	int i;
	int cqe_size = cq->buf.entry_size;
	int cqe_inc = cqe_size == 64 ? 1 : 0;

	i = cq->mcq.cons_index;
	cqe = get_cqe(cq, i & cq->ibcq.cqe);
	cqe += cqe_inc;

	while ((cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) != MLX4_CQE_OPCODE_RESIZE) {
		new_cqe = get_cqe_from_buf(&cq->resize_buf->buf,
					   (i + 1) & cq->resize_buf->cqe);
		memcpy(new_cqe, get_cqe(cq, i & cq->ibcq.cqe), cqe_size);
		new_cqe += cqe_inc;

		new_cqe->owner_sr_opcode = (cqe->owner_sr_opcode & ~MLX4_CQE_OWNER_MASK) |
			(((i + 1) & (cq->resize_buf->cqe + 1)) ? MLX4_CQE_OWNER_MASK : 0);
		cqe = get_cqe(cq, ++i & cq->ibcq.cqe);
		cqe += cqe_inc;
	}
	++cq->mcq.cons_index;
}