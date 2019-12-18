#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_18__ {int /*<<< orphan*/  vpath_open_fail; int /*<<< orphan*/  vpaths_open; } ;
struct TYPE_30__ {int /*<<< orphan*/  fifo_indicate_max_pkts; scalar_t__ tx_steering_type; } ;
struct vxgedev {int no_of_vpath; int /*<<< orphan*/  vpaths_deployed; TYPE_15__* ndev; TYPE_12__ stats; int /*<<< orphan*/  vlan_tag_strip; TYPE_14__** vp_handles; int /*<<< orphan*/  rx_hwts; TYPE_9__ config; int /*<<< orphan*/  pdev; TYPE_13__* devh; int /*<<< orphan*/  mtu; int /*<<< orphan*/  titan1; struct vxge_vpath* vpaths; } ;
struct TYPE_29__ {int /*<<< orphan*/  syncp; } ;
struct TYPE_17__ {int /*<<< orphan*/  vlan_tag_strip; int /*<<< orphan*/  rx_hwts; scalar_t__ rx_vector_no; TYPE_8__ stats; struct __vxge_hw_ring* handle; int /*<<< orphan*/  pdev; TYPE_15__* ndev; } ;
struct TYPE_28__ {int /*<<< orphan*/  syncp; } ;
struct TYPE_16__ {scalar_t__ tx_vector_no; int /*<<< orphan*/  indicate_max_pkts; void* txq; TYPE_7__ stats; int /*<<< orphan*/  pdev; TYPE_15__* ndev; scalar_t__ tx_steering_type; struct __vxge_hw_fifo* handle; } ;
struct vxge_vpath {size_t device_id; int is_open; TYPE_14__* handle; TYPE_11__ ring; TYPE_10__ fifo; int /*<<< orphan*/  is_configured; } ;
struct vxge_tx_priv {int dummy; } ;
struct vxge_rx_priv {int dummy; } ;
struct TYPE_27__ {int per_rxd_space; TYPE_11__* userdata; int /*<<< orphan*/  rxd_term; int /*<<< orphan*/  rxd_init; int /*<<< orphan*/  callback; } ;
struct TYPE_26__ {int per_txdl_space; TYPE_10__* userdata; int /*<<< orphan*/  txdl_term; int /*<<< orphan*/  callback; } ;
struct vxge_hw_vpath_attr {size_t vp_id; TYPE_6__ ring_attr; TYPE_5__ fifo_attr; } ;
struct TYPE_25__ {int /*<<< orphan*/  rtimer_val; int /*<<< orphan*/  ltimer_val; int /*<<< orphan*/  uec_d; int /*<<< orphan*/  uec_c; int /*<<< orphan*/  uec_b; int /*<<< orphan*/  uec_a; } ;
struct TYPE_24__ {int /*<<< orphan*/  urange_c; int /*<<< orphan*/  urange_b; int /*<<< orphan*/  urange_a; } ;
struct vxge_hw_vp_config {TYPE_4__ tti; TYPE_3__ rti; } ;
struct __vxge_hw_ring {int dummy; } ;
struct __vxge_hw_fifo {int dummy; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_23__ {struct vxge_hw_vp_config* vp_config; } ;
struct TYPE_22__ {int /*<<< orphan*/  vp_id; } ;
struct TYPE_21__ {int /*<<< orphan*/  name; } ;
struct TYPE_20__ {TYPE_1__* vpath; } ;
struct TYPE_19__ {TYPE_2__ config; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  RTI_T1A_RX_URANGE_A ; 
 int /*<<< orphan*/  RTI_T1A_RX_URANGE_B ; 
 int /*<<< orphan*/  RTI_T1A_RX_URANGE_C ; 
 int /*<<< orphan*/  TTI_T1A_TX_UFC_A ; 
 int /*<<< orphan*/  TTI_T1A_TX_UFC_B ; 
 int /*<<< orphan*/  TTI_T1A_TX_UFC_C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTI_T1A_TX_UFC_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VXGE_ERR ; 
 int VXGE_HW_OK ; 
 int /*<<< orphan*/  VXGE_T1A_TTI_LTIMER_VAL ; 
 int /*<<< orphan*/  VXGE_T1A_TTI_RTIMER_VAL ; 
 void* netdev_get_tx_queue (TYPE_15__*,int) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxge_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_close_vpaths (struct vxgedev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_debug_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,int) ; 
 int vxge_hw_vpath_open (TYPE_13__*,struct vxge_hw_vpath_attr*,TYPE_14__**) ; 
 int /*<<< orphan*/  vxge_mBIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_rx_1b_compl ; 
 int /*<<< orphan*/  vxge_rx_initial_replenish ; 
 int /*<<< orphan*/  vxge_rx_term ; 
 int /*<<< orphan*/  vxge_tx_term ; 
 int /*<<< orphan*/  vxge_xmit_compl ; 

__attribute__((used)) static int vxge_open_vpaths(struct vxgedev *vdev)
{
	struct vxge_hw_vpath_attr attr;
	enum vxge_hw_status status;
	struct vxge_vpath *vpath;
	u32 vp_id = 0;
	int i;

	for (i = 0; i < vdev->no_of_vpath; i++) {
		vpath = &vdev->vpaths[i];
		vxge_assert(vpath->is_configured);

		if (!vdev->titan1) {
			struct vxge_hw_vp_config *vcfg;
			vcfg = &vdev->devh->config.vp_config[vpath->device_id];

			vcfg->rti.urange_a = RTI_T1A_RX_URANGE_A;
			vcfg->rti.urange_b = RTI_T1A_RX_URANGE_B;
			vcfg->rti.urange_c = RTI_T1A_RX_URANGE_C;
			vcfg->tti.uec_a = TTI_T1A_TX_UFC_A;
			vcfg->tti.uec_b = TTI_T1A_TX_UFC_B;
			vcfg->tti.uec_c = TTI_T1A_TX_UFC_C(vdev->mtu);
			vcfg->tti.uec_d = TTI_T1A_TX_UFC_D(vdev->mtu);
			vcfg->tti.ltimer_val = VXGE_T1A_TTI_LTIMER_VAL;
			vcfg->tti.rtimer_val = VXGE_T1A_TTI_RTIMER_VAL;
		}

		attr.vp_id = vpath->device_id;
		attr.fifo_attr.callback = vxge_xmit_compl;
		attr.fifo_attr.txdl_term = vxge_tx_term;
		attr.fifo_attr.per_txdl_space = sizeof(struct vxge_tx_priv);
		attr.fifo_attr.userdata = &vpath->fifo;

		attr.ring_attr.callback = vxge_rx_1b_compl;
		attr.ring_attr.rxd_init = vxge_rx_initial_replenish;
		attr.ring_attr.rxd_term = vxge_rx_term;
		attr.ring_attr.per_rxd_space = sizeof(struct vxge_rx_priv);
		attr.ring_attr.userdata = &vpath->ring;

		vpath->ring.ndev = vdev->ndev;
		vpath->ring.pdev = vdev->pdev;

		status = vxge_hw_vpath_open(vdev->devh, &attr, &vpath->handle);
		if (status == VXGE_HW_OK) {
			vpath->fifo.handle =
			    (struct __vxge_hw_fifo *)attr.fifo_attr.userdata;
			vpath->ring.handle =
			    (struct __vxge_hw_ring *)attr.ring_attr.userdata;
			vpath->fifo.tx_steering_type =
				vdev->config.tx_steering_type;
			vpath->fifo.ndev = vdev->ndev;
			vpath->fifo.pdev = vdev->pdev;

			u64_stats_init(&vpath->fifo.stats.syncp);
			u64_stats_init(&vpath->ring.stats.syncp);

			if (vdev->config.tx_steering_type)
				vpath->fifo.txq =
					netdev_get_tx_queue(vdev->ndev, i);
			else
				vpath->fifo.txq =
					netdev_get_tx_queue(vdev->ndev, 0);
			vpath->fifo.indicate_max_pkts =
				vdev->config.fifo_indicate_max_pkts;
			vpath->fifo.tx_vector_no = 0;
			vpath->ring.rx_vector_no = 0;
			vpath->ring.rx_hwts = vdev->rx_hwts;
			vpath->is_open = 1;
			vdev->vp_handles[i] = vpath->handle;
			vpath->ring.vlan_tag_strip = vdev->vlan_tag_strip;
			vdev->stats.vpaths_open++;
		} else {
			vdev->stats.vpath_open_fail++;
			vxge_debug_init(VXGE_ERR, "%s: vpath: %d failed to "
					"open with status: %d",
					vdev->ndev->name, vpath->device_id,
					status);
			vxge_close_vpaths(vdev, 0);
			return -EPERM;
		}

		vp_id = vpath->handle->vpath->vp_id;
		vdev->vpaths_deployed |= vxge_mBIT(vp_id);
	}

	return VXGE_HW_OK;
}