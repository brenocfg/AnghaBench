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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mlx5_ib_ubuffer {int /*<<< orphan*/ * umem; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  mqp; } ;
struct mlx5_ib_sq {int tisn; struct mlx5_ib_ubuffer ubuffer; TYPE_1__ base; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int dummy; } ;
typedef  void __be64 ;
struct TYPE_4__ {int uid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_ADAPTER_PAGE_SHIFT ; 
 void* MLX5_ADDR_OF (void*,void*,void*) ; 
 scalar_t__ MLX5_CAP_ETH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_GET (void*,void*,struct ib_pd*) ; 
 int /*<<< orphan*/  MLX5_GET64 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SEND_WQE_BB ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,struct ib_pd*,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_SQC_STATE_RST ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 int MLX5_WQ_TYPE_CYCLIC ; 
 struct ib_pd* allow_multi_pkt_send_wqe ; 
 struct ib_pd* allow_swp ; 
 struct ib_pd* cqn ; 
 struct ib_pd* cqn_snd ; 
 void* create_qp_in ; 
 void* create_sq_in ; 
 void* ctx ; 
 int /*<<< orphan*/  dbr_addr ; 
 int /*<<< orphan*/  eth_net_offloads ; 
 struct ib_pd* flush_in_error_en ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ *) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_pd* log_sq_size ; 
 struct ib_pd* log_wq_pg_sz ; 
 struct ib_pd* log_wq_stride ; 
 struct ib_pd* log_wq_sz ; 
 int mlx5_core_create_sq_tracked (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_populate_pas (struct mlx5_ib_dev*,int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int mlx5_ib_umem_get (struct mlx5_ib_dev*,struct ib_udata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  multi_pkt_send_wqe ; 
 struct ib_pd* page_offset ; 
 void* qpc ; 
 struct ib_pd* state ; 
 int /*<<< orphan*/  swp ; 
 struct ib_pd* tis_lst_sz ; 
 struct ib_pd* tis_num_0 ; 
 TYPE_2__* to_mpd (struct ib_pd*) ; 
 struct ib_pd* uar_page ; 
 struct ib_pd* uid ; 
 struct ib_pd* user_index ; 
 struct ib_pd* wq_type ; 

__attribute__((used)) static int create_raw_packet_qp_sq(struct mlx5_ib_dev *dev,
				   struct ib_udata *udata,
				   struct mlx5_ib_sq *sq, void *qpin,
				   struct ib_pd *pd)
{
	struct mlx5_ib_ubuffer *ubuffer = &sq->ubuffer;
	__be64 *pas;
	void *in;
	void *sqc;
	void *qpc = MLX5_ADDR_OF(create_qp_in, qpin, qpc);
	void *wq;
	int inlen;
	int err;
	int page_shift = 0;
	int npages;
	int ncont = 0;
	u32 offset = 0;

	err = mlx5_ib_umem_get(dev, udata, ubuffer->buf_addr, ubuffer->buf_size,
			       &sq->ubuffer.umem, &npages, &page_shift, &ncont,
			       &offset);
	if (err)
		return err;

	inlen = MLX5_ST_SZ_BYTES(create_sq_in) + sizeof(u64) * ncont;
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in) {
		err = -ENOMEM;
		goto err_umem;
	}

	MLX5_SET(create_sq_in, in, uid, to_mpd(pd)->uid);
	sqc = MLX5_ADDR_OF(create_sq_in, in, ctx);
	MLX5_SET(sqc, sqc, flush_in_error_en, 1);
	if (MLX5_CAP_ETH(dev->mdev, multi_pkt_send_wqe))
		MLX5_SET(sqc, sqc, allow_multi_pkt_send_wqe, 1);
	MLX5_SET(sqc, sqc, state, MLX5_SQC_STATE_RST);
	MLX5_SET(sqc, sqc, user_index, MLX5_GET(qpc, qpc, user_index));
	MLX5_SET(sqc, sqc, cqn, MLX5_GET(qpc, qpc, cqn_snd));
	MLX5_SET(sqc, sqc, tis_lst_sz, 1);
	MLX5_SET(sqc, sqc, tis_num_0, sq->tisn);
	if (MLX5_CAP_GEN(dev->mdev, eth_net_offloads) &&
	    MLX5_CAP_ETH(dev->mdev, swp))
		MLX5_SET(sqc, sqc, allow_swp, 1);

	wq = MLX5_ADDR_OF(sqc, sqc, wq);
	MLX5_SET(wq, wq, wq_type, MLX5_WQ_TYPE_CYCLIC);
	MLX5_SET(wq, wq, pd, MLX5_GET(qpc, qpc, pd));
	MLX5_SET(wq, wq, uar_page, MLX5_GET(qpc, qpc, uar_page));
	MLX5_SET64(wq, wq, dbr_addr, MLX5_GET64(qpc, qpc, dbr_addr));
	MLX5_SET(wq, wq, log_wq_stride, ilog2(MLX5_SEND_WQE_BB));
	MLX5_SET(wq, wq, log_wq_sz, MLX5_GET(qpc, qpc, log_sq_size));
	MLX5_SET(wq, wq, log_wq_pg_sz,  page_shift - MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET(wq, wq, page_offset, offset);

	pas = (__be64 *)MLX5_ADDR_OF(wq, wq, pas);
	mlx5_ib_populate_pas(dev, sq->ubuffer.umem, page_shift, pas, 0);

	err = mlx5_core_create_sq_tracked(dev->mdev, in, inlen, &sq->base.mqp);

	kvfree(in);

	if (err)
		goto err_umem;

	return 0;

err_umem:
	ib_umem_release(sq->ubuffer.umem);
	sq->ubuffer.umem = NULL;

	return err;
}