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
struct rockchip_rga {int /*<<< orphan*/  dev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  vfd; int /*<<< orphan*/  m2m_dev; scalar_t__ dst_mmu_pages; scalar_t__ src_mmu_pages; int /*<<< orphan*/  cmdbuf_phy; int /*<<< orphan*/  cmdbuf_virt; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_WRITE_COMBINE ; 
 int /*<<< orphan*/  RGA_CMDBUF_SIZE ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 struct rockchip_rga* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rga_remove(struct platform_device *pdev)
{
	struct rockchip_rga *rga = platform_get_drvdata(pdev);

	dma_free_attrs(rga->dev, RGA_CMDBUF_SIZE, rga->cmdbuf_virt,
		       rga->cmdbuf_phy, DMA_ATTR_WRITE_COMBINE);

	free_pages((unsigned long)rga->src_mmu_pages, 3);
	free_pages((unsigned long)rga->dst_mmu_pages, 3);

	v4l2_info(&rga->v4l2_dev, "Removing\n");

	v4l2_m2m_release(rga->m2m_dev);
	video_unregister_device(rga->vfd);
	v4l2_device_unregister(&rga->v4l2_dev);

	pm_runtime_disable(rga->dev);

	return 0;
}