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
struct xdp_frame {unsigned int headroom; void* data; int /*<<< orphan*/  len; } ;
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_3__ {struct device* parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct dpaa2_fd {int dummy; } ;
struct TYPE_4__ {void* dma_size; struct xdp_frame* xdpf; } ;
struct dpaa2_eth_swa {TYPE_2__ xdp; int /*<<< orphan*/  type; } ;
struct dpaa2_eth_priv {int (* enqueue ) (struct dpaa2_eth_priv*,struct dpaa2_eth_fq*,struct dpaa2_fd*,int /*<<< orphan*/ ) ;struct dpaa2_eth_fq* fq; int /*<<< orphan*/  percpu_extras; int /*<<< orphan*/  percpu_stats; } ;
struct dpaa2_eth_fq {int dummy; } ;
struct dpaa2_eth_drv_stats {int tx_portal_busy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  fd ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int DPAA2_ETH_ENQUEUE_RETRIES ; 
 int /*<<< orphan*/  DPAA2_ETH_SWA_XDP ; 
 int DPAA2_ETH_TX_BUF_ALIGN ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FD_CTRL_PTA ; 
 void* PTR_ALIGN (void*,int) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,void*,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 unsigned int dpaa2_eth_needed_headroom (struct dpaa2_eth_priv*,int /*<<< orphan*/ *) ; 
 size_t dpaa2_eth_queue_count (struct dpaa2_eth_priv*) ; 
 scalar_t__ dpaa2_fd_get_len (struct dpaa2_fd*) ; 
 int /*<<< orphan*/  dpaa2_fd_set_addr (struct dpaa2_fd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_fd_set_ctrl (struct dpaa2_fd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_fd_set_format (struct dpaa2_fd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_fd_set_len (struct dpaa2_fd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_fd_set_offset (struct dpaa2_fd*,int) ; 
 int /*<<< orphan*/  dpaa2_fd_single ; 
 int /*<<< orphan*/  memset (struct dpaa2_fd*,int /*<<< orphan*/ ,int) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 size_t smp_processor_id () ; 
 int stub1 (struct dpaa2_eth_priv*,struct dpaa2_eth_fq*,struct dpaa2_fd*,int /*<<< orphan*/ ) ; 
 void* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dpaa2_eth_xdp_xmit_frame(struct net_device *net_dev,
				    struct xdp_frame *xdpf)
{
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	struct device *dev = net_dev->dev.parent;
	struct rtnl_link_stats64 *percpu_stats;
	struct dpaa2_eth_drv_stats *percpu_extras;
	unsigned int needed_headroom;
	struct dpaa2_eth_swa *swa;
	struct dpaa2_eth_fq *fq;
	struct dpaa2_fd fd;
	void *buffer_start, *aligned_start;
	dma_addr_t addr;
	int err, i;

	/* We require a minimum headroom to be able to transmit the frame.
	 * Otherwise return an error and let the original net_device handle it
	 */
	needed_headroom = dpaa2_eth_needed_headroom(priv, NULL);
	if (xdpf->headroom < needed_headroom)
		return -EINVAL;

	percpu_stats = this_cpu_ptr(priv->percpu_stats);
	percpu_extras = this_cpu_ptr(priv->percpu_extras);

	/* Setup the FD fields */
	memset(&fd, 0, sizeof(fd));

	/* Align FD address, if possible */
	buffer_start = xdpf->data - needed_headroom;
	aligned_start = PTR_ALIGN(buffer_start - DPAA2_ETH_TX_BUF_ALIGN,
				  DPAA2_ETH_TX_BUF_ALIGN);
	if (aligned_start >= xdpf->data - xdpf->headroom)
		buffer_start = aligned_start;

	swa = (struct dpaa2_eth_swa *)buffer_start;
	/* fill in necessary fields here */
	swa->type = DPAA2_ETH_SWA_XDP;
	swa->xdp.dma_size = xdpf->data + xdpf->len - buffer_start;
	swa->xdp.xdpf = xdpf;

	addr = dma_map_single(dev, buffer_start,
			      swa->xdp.dma_size,
			      DMA_BIDIRECTIONAL);
	if (unlikely(dma_mapping_error(dev, addr))) {
		percpu_stats->tx_dropped++;
		return -ENOMEM;
	}

	dpaa2_fd_set_addr(&fd, addr);
	dpaa2_fd_set_offset(&fd, xdpf->data - buffer_start);
	dpaa2_fd_set_len(&fd, xdpf->len);
	dpaa2_fd_set_format(&fd, dpaa2_fd_single);
	dpaa2_fd_set_ctrl(&fd, FD_CTRL_PTA);

	fq = &priv->fq[smp_processor_id() % dpaa2_eth_queue_count(priv)];
	for (i = 0; i < DPAA2_ETH_ENQUEUE_RETRIES; i++) {
		err = priv->enqueue(priv, fq, &fd, 0);
		if (err != -EBUSY)
			break;
	}
	percpu_extras->tx_portal_busy += i;
	if (unlikely(err < 0)) {
		percpu_stats->tx_errors++;
		/* let the Rx device handle the cleanup */
		return err;
	}

	percpu_stats->tx_packets++;
	percpu_stats->tx_bytes += dpaa2_fd_get_len(&fd);

	return 0;
}