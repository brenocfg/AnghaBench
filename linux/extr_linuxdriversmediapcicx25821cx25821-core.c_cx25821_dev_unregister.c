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
struct cx25821_dev {int /*<<< orphan*/ * i2c_bus; int /*<<< orphan*/  pci; int /*<<< orphan*/  base_io_addr; } ;

/* Variables and functions */
 int MAX_VID_CAP_CHANNEL_NUM ; 
 int SRAM_CH08 ; 
 int /*<<< orphan*/  cx25821_i2c_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx25821_iounmap (struct cx25821_dev*) ; 
 int /*<<< orphan*/  cx25821_video_unregister (struct cx25821_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx25821_dev_unregister(struct cx25821_dev *dev)
{
	int i;

	if (!dev->base_io_addr)
		return;

	release_mem_region(dev->base_io_addr, pci_resource_len(dev->pci, 0));

	for (i = 0; i < MAX_VID_CAP_CHANNEL_NUM - 1; i++) {
		if (i == SRAM_CH08) /* audio channel */
			continue;
		/*
		 * TODO: enable when video output is properly
		 * supported.
		if (i == SRAM_CH09 || i == SRAM_CH10)
			cx25821_free_mem_upstream(&dev->channels[i]);
		 */
		cx25821_video_unregister(dev, i);
	}

	cx25821_i2c_unregister(&dev->i2c_bus[0]);
	cx25821_iounmap(dev);
}