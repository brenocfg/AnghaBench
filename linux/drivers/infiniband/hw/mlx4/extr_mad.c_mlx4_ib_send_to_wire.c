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
typedef  int u8 ;
typedef  int u64 ;
typedef  void* u32 ;
typedef  size_t u16 ;
struct rdma_ah_attr {int dummy; } ;
struct mlx4_mad_snd_buf {int /*<<< orphan*/  payload; } ;
struct TYPE_9__ {size_t*** virt2phys_pkey; } ;
struct TYPE_8__ {struct mlx4_ib_demux_pv_ctx** sqps; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  ib_dev; TYPE_2__ pkeys; TYPE_1__ sriov; } ;
struct mlx4_ib_demux_pv_qp {int tx_ix_head; int tx_ix_tail; TYPE_5__* tx_ring; int /*<<< orphan*/  tx_lock; struct ib_qp* qp; } ;
struct mlx4_ib_demux_pv_ctx {scalar_t__ state; TYPE_4__* pd; struct mlx4_ib_demux_pv_qp* qp; } ;
struct TYPE_14__ {int wr_id; int num_sge; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  opcode; struct ib_sge* sg_list; int /*<<< orphan*/ * next; } ;
struct ib_ud_wr {int port_num; size_t pkey_index; TYPE_7__ wr; void* remote_qpn; void* remote_qkey; struct ib_ah* ah; } ;
struct ib_sge {int length; int /*<<< orphan*/  lkey; int /*<<< orphan*/  addr; } ;
struct ib_send_wr {int dummy; } ;
struct ib_qp {int dummy; } ;
struct ib_mad {int dummy; } ;
struct ib_ah {TYPE_4__* pd; int /*<<< orphan*/  device; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_13__ {int /*<<< orphan*/  sgid_index; } ;
struct TYPE_10__ {int /*<<< orphan*/  map; scalar_t__ addr; } ;
struct TYPE_12__ {struct ib_ah* ah; TYPE_3__ buf; } ;
struct TYPE_11__ {int /*<<< orphan*/  local_dma_lkey; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ DEMUX_PV_STATE_ACTIVE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int IB_QPT_SMI ; 
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int MLX4_NUM_TUNNEL_BUFS ; 
 int MLX4_TUN_SET_WRID_QPN (int) ; 
 int /*<<< orphan*/  ib_ah ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ib_post_send (struct ib_qp*,TYPE_7__*,struct ib_send_wr const**) ; 
 int /*<<< orphan*/  kfree (struct ib_ah*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ib_mad*,int) ; 
 int mlx4_ib_create_ah_slave (struct ib_ah*,struct rdma_ah_attr*,int /*<<< orphan*/ ,int*,size_t) ; 
 TYPE_6__* rdma_ah_retrieve_grh (struct rdma_ah_attr*) ; 
 struct ib_ah* rdma_zalloc_drv_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int mlx4_ib_send_to_wire(struct mlx4_ib_dev *dev, int slave, u8 port,
			 enum ib_qp_type dest_qpt, u16 pkey_index,
			 u32 remote_qpn, u32 qkey, struct rdma_ah_attr *attr,
			 u8 *s_mac, u16 vlan_id, struct ib_mad *mad)
{
	struct ib_sge list;
	struct ib_ud_wr wr;
	const struct ib_send_wr *bad_wr;
	struct mlx4_ib_demux_pv_ctx *sqp_ctx;
	struct mlx4_ib_demux_pv_qp *sqp;
	struct mlx4_mad_snd_buf *sqp_mad;
	struct ib_ah *ah;
	struct ib_qp *send_qp = NULL;
	unsigned wire_tx_ix = 0;
	u16 wire_pkey_ix;
	int src_qpnum;
	int ret;

	sqp_ctx = dev->sriov.sqps[port-1];

	/* check if proxy qp created */
	if (!sqp_ctx || sqp_ctx->state != DEMUX_PV_STATE_ACTIVE)
		return -EAGAIN;

	if (dest_qpt == IB_QPT_SMI) {
		src_qpnum = 0;
		sqp = &sqp_ctx->qp[0];
		wire_pkey_ix = dev->pkeys.virt2phys_pkey[slave][port - 1][0];
	} else {
		src_qpnum = 1;
		sqp = &sqp_ctx->qp[1];
		wire_pkey_ix = dev->pkeys.virt2phys_pkey[slave][port - 1][pkey_index];
	}

	send_qp = sqp->qp;

	ah = rdma_zalloc_drv_obj(sqp_ctx->pd->device, ib_ah);
	if (!ah)
		return -ENOMEM;

	ah->device = sqp_ctx->pd->device;
	ah->pd = sqp_ctx->pd;

	/* create ah */
	ret = mlx4_ib_create_ah_slave(ah, attr,
				      rdma_ah_retrieve_grh(attr)->sgid_index,
				      s_mac, vlan_id);
	if (ret)
		goto out;

	spin_lock(&sqp->tx_lock);
	if (sqp->tx_ix_head - sqp->tx_ix_tail >=
	    (MLX4_NUM_TUNNEL_BUFS - 1))
		ret = -EAGAIN;
	else
		wire_tx_ix = (++sqp->tx_ix_head) & (MLX4_NUM_TUNNEL_BUFS - 1);
	spin_unlock(&sqp->tx_lock);
	if (ret)
		goto out;

	sqp_mad = (struct mlx4_mad_snd_buf *) (sqp->tx_ring[wire_tx_ix].buf.addr);
	kfree(sqp->tx_ring[wire_tx_ix].ah);
	sqp->tx_ring[wire_tx_ix].ah = ah;
	ib_dma_sync_single_for_cpu(&dev->ib_dev,
				   sqp->tx_ring[wire_tx_ix].buf.map,
				   sizeof (struct mlx4_mad_snd_buf),
				   DMA_TO_DEVICE);

	memcpy(&sqp_mad->payload, mad, sizeof *mad);

	ib_dma_sync_single_for_device(&dev->ib_dev,
				      sqp->tx_ring[wire_tx_ix].buf.map,
				      sizeof (struct mlx4_mad_snd_buf),
				      DMA_TO_DEVICE);

	list.addr = sqp->tx_ring[wire_tx_ix].buf.map;
	list.length = sizeof (struct mlx4_mad_snd_buf);
	list.lkey = sqp_ctx->pd->local_dma_lkey;

	wr.ah = ah;
	wr.port_num = port;
	wr.pkey_index = wire_pkey_ix;
	wr.remote_qkey = qkey;
	wr.remote_qpn = remote_qpn;
	wr.wr.next = NULL;
	wr.wr.wr_id = ((u64) wire_tx_ix) | MLX4_TUN_SET_WRID_QPN(src_qpnum);
	wr.wr.sg_list = &list;
	wr.wr.num_sge = 1;
	wr.wr.opcode = IB_WR_SEND;
	wr.wr.send_flags = IB_SEND_SIGNALED;

	ret = ib_post_send(send_qp, &wr.wr, &bad_wr);
	if (!ret)
		return 0;

	spin_lock(&sqp->tx_lock);
	sqp->tx_ix_tail++;
	spin_unlock(&sqp->tx_lock);
	sqp->tx_ring[wire_tx_ix].ah = NULL;
out:
	kfree(ah);
	return ret;
}