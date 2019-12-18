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
struct s5p_mfc_dev {int /*<<< orphan*/  mem_bitmap; int /*<<< orphan*/  mem_base; int /*<<< orphan*/  mem_virt; int /*<<< orphan*/  mem_size; TYPE_1__* plat_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_clear_max_seg_size (struct device*) ; 

__attribute__((used)) static void s5p_mfc_unconfigure_common_memory(struct s5p_mfc_dev *mfc_dev)
{
	struct device *dev = &mfc_dev->plat_dev->dev;

	dma_free_coherent(dev, mfc_dev->mem_size, mfc_dev->mem_virt,
			  mfc_dev->mem_base);
	kfree(mfc_dev->mem_bitmap);
	vb2_dma_contig_clear_max_seg_size(dev);
}