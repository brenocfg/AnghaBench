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
struct qm_sg_entry {int dummy; } ;
struct qm_fd {int /*<<< orphan*/  bpid; } ;
struct net_device {int dummy; } ;
struct dpaa_bp {int /*<<< orphan*/  dev; int /*<<< orphan*/  size; } ;
struct bm_buffer {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  bm_buffer_set64 (struct bm_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa_bman_release (struct dpaa_bp*,struct bm_buffer*,int) ; 
 struct dpaa_bp* dpaa_bpid2pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa_release_sgt_members (struct qm_sg_entry*) ; 
 void* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_fd_addr (struct qm_fd const*) ; 
 scalar_t__ qm_fd_get_format (struct qm_fd const*) ; 
 int qm_fd_get_offset (struct qm_fd const*) ; 
 scalar_t__ qm_fd_sg ; 

__attribute__((used)) static void dpaa_fd_release(const struct net_device *net_dev,
			    const struct qm_fd *fd)
{
	struct qm_sg_entry *sgt;
	struct dpaa_bp *dpaa_bp;
	struct bm_buffer bmb;
	dma_addr_t addr;
	void *vaddr;

	bmb.data = 0;
	bm_buffer_set64(&bmb, qm_fd_addr(fd));

	dpaa_bp = dpaa_bpid2pool(fd->bpid);
	if (!dpaa_bp)
		return;

	if (qm_fd_get_format(fd) == qm_fd_sg) {
		vaddr = phys_to_virt(qm_fd_addr(fd));
		sgt = vaddr + qm_fd_get_offset(fd);

		dma_unmap_single(dpaa_bp->dev, qm_fd_addr(fd), dpaa_bp->size,
				 DMA_FROM_DEVICE);

		dpaa_release_sgt_members(sgt);

		addr = dma_map_single(dpaa_bp->dev, vaddr, dpaa_bp->size,
				      DMA_FROM_DEVICE);
		if (dma_mapping_error(dpaa_bp->dev, addr)) {
			dev_err(dpaa_bp->dev, "DMA mapping failed");
			return;
		}
		bm_buffer_set64(&bmb, addr);
	}

	dpaa_bman_release(dpaa_bp, &bmb, 1);
}