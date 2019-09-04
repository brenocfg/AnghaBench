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
struct scif_hw_dev {int dummy; } ;
struct mic_device {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 struct scif_hw_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  mic_unmap_single (struct mic_device*,int /*<<< orphan*/ ,size_t) ; 
 struct mic_device* scdev_to_mdev (struct scif_hw_dev*) ; 

__attribute__((used)) static void __mic_dma_free(struct device *dev, size_t size, void *vaddr,
			   dma_addr_t dma_handle, unsigned long attrs)
{
	struct scif_hw_dev *scdev = dev_get_drvdata(dev);
	struct mic_device *mdev = scdev_to_mdev(scdev);

	mic_unmap_single(mdev, dma_handle, size);
	kfree(vaddr);
}