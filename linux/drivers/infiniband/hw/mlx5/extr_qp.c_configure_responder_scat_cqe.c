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
struct ib_qp_init_attr {scalar_t__ qp_type; int /*<<< orphan*/  recv_cq; } ;

/* Variables and functions */
 scalar_t__ MLX5_IB_QPT_DCI ; 
 scalar_t__ MLX5_IB_QPT_DCT ; 
 int /*<<< orphan*/  MLX5_RES_SCAT_DATA32_CQE ; 
 int /*<<< orphan*/  MLX5_RES_SCAT_DATA64_CQE ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_res ; 
 void* dctc ; 
 int mlx5_ib_get_cqe_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void configure_responder_scat_cqe(struct ib_qp_init_attr *init_attr,
					 void *qpc)
{
	int rcqe_sz;

	if (init_attr->qp_type == MLX5_IB_QPT_DCI)
		return;

	rcqe_sz = mlx5_ib_get_cqe_size(init_attr->recv_cq);

	if (init_attr->qp_type == MLX5_IB_QPT_DCT) {
		if (rcqe_sz == 128)
			MLX5_SET(dctc, qpc, cs_res, MLX5_RES_SCAT_DATA64_CQE);

		return;
	}

	MLX5_SET(qpc, qpc, cs_res,
		 rcqe_sz == 128 ? MLX5_RES_SCAT_DATA64_CQE :
				  MLX5_RES_SCAT_DATA32_CQE);
}