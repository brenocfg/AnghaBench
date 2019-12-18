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
typedef  int /*<<< orphan*/  u16 ;
struct page {int dummy; } ;
struct dpaa2_eth_priv {TYPE_2__* net_dev; } ;
struct dpaa2_eth_channel {int /*<<< orphan*/  dpio; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int DPAA2_ETH_BUFS_PER_CMD ; 
 int /*<<< orphan*/  DPAA2_ETH_RX_BUF_RAW_SIZE ; 
 int /*<<< orphan*/  DPAA2_ETH_RX_BUF_SIZE ; 
 int EBUSY ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct page* dev_alloc_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_page (struct device*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int dpaa2_io_service_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_bufs (struct dpaa2_eth_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_dpaa2_eth_buf_seed (TYPE_2__*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_bufs(struct dpaa2_eth_priv *priv,
		    struct dpaa2_eth_channel *ch, u16 bpid)
{
	struct device *dev = priv->net_dev->dev.parent;
	u64 buf_array[DPAA2_ETH_BUFS_PER_CMD];
	struct page *page;
	dma_addr_t addr;
	int i, err;

	for (i = 0; i < DPAA2_ETH_BUFS_PER_CMD; i++) {
		/* Allocate buffer visible to WRIOP + skb shared info +
		 * alignment padding
		 */
		/* allocate one page for each Rx buffer. WRIOP sees
		 * the entire page except for a tailroom reserved for
		 * skb shared info
		 */
		page = dev_alloc_pages(0);
		if (!page)
			goto err_alloc;

		addr = dma_map_page(dev, page, 0, DPAA2_ETH_RX_BUF_SIZE,
				    DMA_BIDIRECTIONAL);
		if (unlikely(dma_mapping_error(dev, addr)))
			goto err_map;

		buf_array[i] = addr;

		/* tracing point */
		trace_dpaa2_eth_buf_seed(priv->net_dev,
					 page, DPAA2_ETH_RX_BUF_RAW_SIZE,
					 addr, DPAA2_ETH_RX_BUF_SIZE,
					 bpid);
	}

release_bufs:
	/* In case the portal is busy, retry until successful */
	while ((err = dpaa2_io_service_release(ch->dpio, bpid,
					       buf_array, i)) == -EBUSY)
		cpu_relax();

	/* If release command failed, clean up and bail out;
	 * not much else we can do about it
	 */
	if (err) {
		free_bufs(priv, buf_array, i);
		return 0;
	}

	return i;

err_map:
	__free_pages(page, 0);
err_alloc:
	/* If we managed to allocate at least some buffers,
	 * release them to hardware
	 */
	if (i)
		goto release_bufs;

	return 0;
}