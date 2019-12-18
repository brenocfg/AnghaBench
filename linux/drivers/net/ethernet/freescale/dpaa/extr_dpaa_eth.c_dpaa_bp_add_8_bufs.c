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
typedef  int u8 ;
struct dpaa_bp {struct device* dev; int /*<<< orphan*/  size; int /*<<< orphan*/  raw_size; } ;
struct device {int dummy; } ;
struct bm_buffer {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 void* PTR_ALIGN (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_CACHE_BYTES ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  bm_buffer_set64 (struct bm_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int dpaa_bman_release (struct dpaa_bp const*,struct bm_buffer*,int) ; 
 scalar_t__ likely (int) ; 
 void* netdev_alloc_frag (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dpaa_bp_add_8_bufs(const struct dpaa_bp *dpaa_bp)
{
	struct device *dev = dpaa_bp->dev;
	struct bm_buffer bmb[8];
	dma_addr_t addr;
	void *new_buf;
	u8 i;

	for (i = 0; i < 8; i++) {
		new_buf = netdev_alloc_frag(dpaa_bp->raw_size);
		if (unlikely(!new_buf)) {
			dev_err(dev, "netdev_alloc_frag() failed, size %zu\n",
				dpaa_bp->raw_size);
			goto release_previous_buffs;
		}
		new_buf = PTR_ALIGN(new_buf, SMP_CACHE_BYTES);

		addr = dma_map_single(dev, new_buf,
				      dpaa_bp->size, DMA_FROM_DEVICE);
		if (unlikely(dma_mapping_error(dev, addr))) {
			dev_err(dpaa_bp->dev, "DMA map failed");
			goto release_previous_buffs;
		}

		bmb[i].data = 0;
		bm_buffer_set64(&bmb[i], addr);
	}

release_bufs:
	return dpaa_bman_release(dpaa_bp, bmb, i);

release_previous_buffs:
	WARN_ONCE(1, "dpaa_eth: failed to add buffers on Rx\n");

	bm_buffer_set64(&bmb[i], 0);
	/* Avoid releasing a completely null buffer; bman_release() requires
	 * at least one buffer.
	 */
	if (likely(i))
		goto release_bufs;

	return 0;
}