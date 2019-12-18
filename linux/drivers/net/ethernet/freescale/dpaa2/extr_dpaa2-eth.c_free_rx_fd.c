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
typedef  scalar_t__ u8 ;
struct dpaa2_sg_entry {int dummy; } ;
struct dpaa2_fd {int dummy; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  iommu_domain; TYPE_2__* net_dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int DPAA2_ETH_MAX_SG_ENTRIES ; 
 int /*<<< orphan*/  DPAA2_ETH_RX_BUF_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_fd_get_addr (struct dpaa2_fd const*) ; 
 scalar_t__ dpaa2_fd_get_format (struct dpaa2_fd const*) ; 
 int dpaa2_fd_get_offset (struct dpaa2_fd const*) ; 
 scalar_t__ dpaa2_fd_sg ; 
 scalar_t__ dpaa2_fd_single ; 
 void* dpaa2_iova_to_virt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_sg_get_addr (struct dpaa2_sg_entry*) ; 
 scalar_t__ dpaa2_sg_is_final (struct dpaa2_sg_entry*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_rx_fd(struct dpaa2_eth_priv *priv,
		       const struct dpaa2_fd *fd,
		       void *vaddr)
{
	struct device *dev = priv->net_dev->dev.parent;
	dma_addr_t addr = dpaa2_fd_get_addr(fd);
	u8 fd_format = dpaa2_fd_get_format(fd);
	struct dpaa2_sg_entry *sgt;
	void *sg_vaddr;
	int i;

	/* If single buffer frame, just free the data buffer */
	if (fd_format == dpaa2_fd_single)
		goto free_buf;
	else if (fd_format != dpaa2_fd_sg)
		/* We don't support any other format */
		return;

	/* For S/G frames, we first need to free all SG entries
	 * except the first one, which was taken care of already
	 */
	sgt = vaddr + dpaa2_fd_get_offset(fd);
	for (i = 1; i < DPAA2_ETH_MAX_SG_ENTRIES; i++) {
		addr = dpaa2_sg_get_addr(&sgt[i]);
		sg_vaddr = dpaa2_iova_to_virt(priv->iommu_domain, addr);
		dma_unmap_page(dev, addr, DPAA2_ETH_RX_BUF_SIZE,
			       DMA_BIDIRECTIONAL);

		free_pages((unsigned long)sg_vaddr, 0);
		if (dpaa2_sg_is_final(&sgt[i]))
			break;
	}

free_buf:
	free_pages((unsigned long)vaddr, 0);
}