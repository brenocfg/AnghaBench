#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_8__ {int /*<<< orphan*/  dma; } ;
struct mlx5_ib_rwq {int rq_num_pas; int user_index; int create_flags; int log_rq_stride; int two_byte_shift_en; int single_stride_log_num_of_bytes; int log_num_strides; int log_rq_size; int rq_page_offset; int log_page_size; int wq_sig; int /*<<< orphan*/  core_qp; int /*<<< orphan*/  page_shift; int /*<<< orphan*/  umem; TYPE_2__ db; } ;
struct TYPE_9__ {int raw_packet_caps; } ;
struct TYPE_10__ {TYPE_3__ attrs; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; TYPE_4__ ib_dev; } ;
struct ib_wq_init_attr {int create_flags; int /*<<< orphan*/  cq; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_7__ {int cqn; } ;
struct TYPE_12__ {TYPE_1__ mcq; } ;
struct TYPE_11__ {int uid; int pdn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_RAW_PACKET_CAP_DELAY_DROP ; 
 int IB_WQ_FLAGS_CVLAN_STRIPPING ; 
 int IB_WQ_FLAGS_DELAY_DROP ; 
 int IB_WQ_FLAGS_PCI_WRITE_END_PADDING ; 
 int IB_WQ_FLAGS_SCATTER_FCS ; 
 void* MLX5_ADDR_OF (void*,void*,void*) ; 
 scalar_t__ MLX5_CAP_ETH (int /*<<< orphan*/ ,struct ib_pd*) ; 
 int MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_IB_WQ_FLAGS_DELAY_DROP ; 
 int MLX5_IB_WQ_FLAGS_STRIDING_RQ ; 
 int MLX5_MIN_SINGLE_STRIDE_LOG_NUM_BYTES ; 
 int MLX5_MIN_SINGLE_WQE_LOG_NUM_STRIDES ; 
 int MLX5_RQC_MEM_RQ_TYPE_MEMORY_RQ_INLINE ; 
 int MLX5_RQC_STATE_RST ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,struct ib_pd*,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 int MLX5_WQ_END_PAD_MODE_ALIGN ; 
 int MLX5_WQ_TYPE_CYCLIC ; 
 int MLX5_WQ_TYPE_CYCLIC_STRIDING_RQ ; 
 struct ib_pd* cqn ; 
 void* create_rq_in ; 
 void* ctx ; 
 int /*<<< orphan*/  dbr_addr ; 
 struct ib_pd* delay_drop_en ; 
 int /*<<< orphan*/  end_pad ; 
 struct ib_pd* end_padding_mode ; 
 int /*<<< orphan*/  eth_net_offloads ; 
 struct ib_pd* flush_in_error_en ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_pd* log_wq_pg_sz ; 
 struct ib_pd* log_wq_stride ; 
 struct ib_pd* log_wq_sz ; 
 struct ib_pd* log_wqe_num_of_strides ; 
 struct ib_pd* log_wqe_stride_size ; 
 struct ib_pd* mem_rq_type ; 
 int mlx5_core_create_rq_tracked (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_destroy_rq_tracked (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_ib_populate_pas (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int) ; 
 struct ib_pd* page_offset ; 
 void* pas ; 
 struct ib_pd* scatter_fcs ; 
 int set_delay_drop (struct mlx5_ib_dev*) ; 
 struct ib_pd* state ; 
 TYPE_6__* to_mcq (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_5__* to_mpd (struct ib_pd*) ; 
 struct ib_pd* two_byte_shift_en ; 
 struct ib_pd* uid ; 
 struct ib_pd* user_index ; 
 struct ib_pd* vlan_cap ; 
 struct ib_pd* vsd ; 
 struct ib_pd* wq_signature ; 
 struct ib_pd* wq_type ; 

__attribute__((used)) static int  create_rq(struct mlx5_ib_rwq *rwq, struct ib_pd *pd,
		      struct ib_wq_init_attr *init_attr)
{
	struct mlx5_ib_dev *dev;
	int has_net_offloads;
	__be64 *rq_pas0;
	void *in;
	void *rqc;
	void *wq;
	int inlen;
	int err;

	dev = to_mdev(pd->device);

	inlen = MLX5_ST_SZ_BYTES(create_rq_in) + sizeof(u64) * rwq->rq_num_pas;
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	MLX5_SET(create_rq_in, in, uid, to_mpd(pd)->uid);
	rqc = MLX5_ADDR_OF(create_rq_in, in, ctx);
	MLX5_SET(rqc,  rqc, mem_rq_type,
		 MLX5_RQC_MEM_RQ_TYPE_MEMORY_RQ_INLINE);
	MLX5_SET(rqc, rqc, user_index, rwq->user_index);
	MLX5_SET(rqc,  rqc, cqn, to_mcq(init_attr->cq)->mcq.cqn);
	MLX5_SET(rqc,  rqc, state, MLX5_RQC_STATE_RST);
	MLX5_SET(rqc,  rqc, flush_in_error_en, 1);
	wq = MLX5_ADDR_OF(rqc, rqc, wq);
	MLX5_SET(wq, wq, wq_type,
		 rwq->create_flags & MLX5_IB_WQ_FLAGS_STRIDING_RQ ?
		 MLX5_WQ_TYPE_CYCLIC_STRIDING_RQ : MLX5_WQ_TYPE_CYCLIC);
	if (init_attr->create_flags & IB_WQ_FLAGS_PCI_WRITE_END_PADDING) {
		if (!MLX5_CAP_GEN(dev->mdev, end_pad)) {
			mlx5_ib_dbg(dev, "Scatter end padding is not supported\n");
			err = -EOPNOTSUPP;
			goto out;
		} else {
			MLX5_SET(wq, wq, end_padding_mode, MLX5_WQ_END_PAD_MODE_ALIGN);
		}
	}
	MLX5_SET(wq, wq, log_wq_stride, rwq->log_rq_stride);
	if (rwq->create_flags & MLX5_IB_WQ_FLAGS_STRIDING_RQ) {
		MLX5_SET(wq, wq, two_byte_shift_en, rwq->two_byte_shift_en);
		MLX5_SET(wq, wq, log_wqe_stride_size,
			 rwq->single_stride_log_num_of_bytes -
			 MLX5_MIN_SINGLE_STRIDE_LOG_NUM_BYTES);
		MLX5_SET(wq, wq, log_wqe_num_of_strides, rwq->log_num_strides -
			 MLX5_MIN_SINGLE_WQE_LOG_NUM_STRIDES);
	}
	MLX5_SET(wq, wq, log_wq_sz, rwq->log_rq_size);
	MLX5_SET(wq, wq, pd, to_mpd(pd)->pdn);
	MLX5_SET(wq, wq, page_offset, rwq->rq_page_offset);
	MLX5_SET(wq, wq, log_wq_pg_sz, rwq->log_page_size);
	MLX5_SET(wq, wq, wq_signature, rwq->wq_sig);
	MLX5_SET64(wq, wq, dbr_addr, rwq->db.dma);
	has_net_offloads = MLX5_CAP_GEN(dev->mdev, eth_net_offloads);
	if (init_attr->create_flags & IB_WQ_FLAGS_CVLAN_STRIPPING) {
		if (!(has_net_offloads && MLX5_CAP_ETH(dev->mdev, vlan_cap))) {
			mlx5_ib_dbg(dev, "VLAN offloads are not supported\n");
			err = -EOPNOTSUPP;
			goto out;
		}
	} else {
		MLX5_SET(rqc, rqc, vsd, 1);
	}
	if (init_attr->create_flags & IB_WQ_FLAGS_SCATTER_FCS) {
		if (!(has_net_offloads && MLX5_CAP_ETH(dev->mdev, scatter_fcs))) {
			mlx5_ib_dbg(dev, "Scatter FCS is not supported\n");
			err = -EOPNOTSUPP;
			goto out;
		}
		MLX5_SET(rqc, rqc, scatter_fcs, 1);
	}
	if (init_attr->create_flags & IB_WQ_FLAGS_DELAY_DROP) {
		if (!(dev->ib_dev.attrs.raw_packet_caps &
		      IB_RAW_PACKET_CAP_DELAY_DROP)) {
			mlx5_ib_dbg(dev, "Delay drop is not supported\n");
			err = -EOPNOTSUPP;
			goto out;
		}
		MLX5_SET(rqc, rqc, delay_drop_en, 1);
	}
	rq_pas0 = (__be64 *)MLX5_ADDR_OF(wq, wq, pas);
	mlx5_ib_populate_pas(dev, rwq->umem, rwq->page_shift, rq_pas0, 0);
	err = mlx5_core_create_rq_tracked(dev->mdev, in, inlen, &rwq->core_qp);
	if (!err && init_attr->create_flags & IB_WQ_FLAGS_DELAY_DROP) {
		err = set_delay_drop(dev);
		if (err) {
			mlx5_ib_warn(dev, "Failed to enable delay drop err=%d\n",
				     err);
			mlx5_core_destroy_rq_tracked(dev->mdev, &rwq->core_qp);
		} else {
			rwq->create_flags |= MLX5_IB_WQ_FLAGS_DELAY_DROP;
		}
	}
out:
	kvfree(in);
	return err;
}