#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct vring_desc {int dummy; } ;
struct virtio_net_hdr {int dummy; } ;
struct virtio_net_config {scalar_t__ mtu; } ;
struct mlxbf_tmfifo_vring {int vdev_id; int cur_len; scalar_t__ pkt_len; scalar_t__ rem_len; struct vring_desc* desc; struct mlxbf_tmfifo* fifo; } ;
struct TYPE_2__ {struct virtio_net_config net; } ;
struct mlxbf_tmfifo_vdev {struct mlxbf_tmfifo_vring* vrings; TYPE_1__ config; } ;
struct mlxbf_tmfifo_msg_hdr {scalar_t__ len; void* type; } ;
struct mlxbf_tmfifo {struct mlxbf_tmfifo_vring** vring; scalar_t__ tx_base; struct mlxbf_tmfifo_vdev** vdev; scalar_t__ rx_base; } ;

/* Variables and functions */
 scalar_t__ MLXBF_TMFIFO_NET_L2_OVERHEAD ; 
 scalar_t__ MLXBF_TMFIFO_RX_DATA ; 
 scalar_t__ MLXBF_TMFIFO_TX_DATA ; 
 size_t MLXBF_TMFIFO_VRING_RX ; 
 void* VIRTIO_ID_CONSOLE ; 
 void* VIRTIO_ID_NET ; 
 scalar_t__ htons (scalar_t__) ; 
 scalar_t__ mlxbf_tmfifo_get_pkt_len (struct mlxbf_tmfifo_vring*,struct vring_desc*) ; 
 scalar_t__ ntohs (scalar_t__) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mlxbf_tmfifo_rxtx_header(struct mlxbf_tmfifo_vring *vring,
				     struct vring_desc *desc,
				     bool is_rx, bool *vring_change)
{
	struct mlxbf_tmfifo *fifo = vring->fifo;
	struct virtio_net_config *config;
	struct mlxbf_tmfifo_msg_hdr hdr;
	int vdev_id, hdr_len;

	/* Read/Write packet header. */
	if (is_rx) {
		/* Drain one word from the FIFO. */
		*(u64 *)&hdr = readq(fifo->rx_base + MLXBF_TMFIFO_RX_DATA);

		/* Skip the length 0 packets (keepalive). */
		if (hdr.len == 0)
			return;

		/* Check packet type. */
		if (hdr.type == VIRTIO_ID_NET) {
			vdev_id = VIRTIO_ID_NET;
			hdr_len = sizeof(struct virtio_net_hdr);
			config = &fifo->vdev[vdev_id]->config.net;
			if (ntohs(hdr.len) > config->mtu +
			    MLXBF_TMFIFO_NET_L2_OVERHEAD)
				return;
		} else {
			vdev_id = VIRTIO_ID_CONSOLE;
			hdr_len = 0;
		}

		/*
		 * Check whether the new packet still belongs to this vring.
		 * If not, update the pkt_len of the new vring.
		 */
		if (vdev_id != vring->vdev_id) {
			struct mlxbf_tmfifo_vdev *tm_dev2 = fifo->vdev[vdev_id];

			if (!tm_dev2)
				return;
			vring->desc = desc;
			vring = &tm_dev2->vrings[MLXBF_TMFIFO_VRING_RX];
			*vring_change = true;
		}
		vring->pkt_len = ntohs(hdr.len) + hdr_len;
	} else {
		/* Network virtio has an extra header. */
		hdr_len = (vring->vdev_id == VIRTIO_ID_NET) ?
			   sizeof(struct virtio_net_hdr) : 0;
		vring->pkt_len = mlxbf_tmfifo_get_pkt_len(vring, desc);
		hdr.type = (vring->vdev_id == VIRTIO_ID_NET) ?
			    VIRTIO_ID_NET : VIRTIO_ID_CONSOLE;
		hdr.len = htons(vring->pkt_len - hdr_len);
		writeq(*(u64 *)&hdr, fifo->tx_base + MLXBF_TMFIFO_TX_DATA);
	}

	vring->cur_len = hdr_len;
	vring->rem_len = vring->pkt_len;
	fifo->vring[is_rx] = vring;
}