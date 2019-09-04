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
struct ngene {int icounts; int device_version; scalar_t__ fw_interface_version; TYPE_2__* channel; scalar_t__ iomem; int /*<<< orphan*/  event_tasklet; TYPE_1__* pci_dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int number; struct ngene* dev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_VER ; 
 int MAX_STREAM ; 
 int /*<<< orphan*/  NGENE_INT_COUNTS ; 
 int /*<<< orphan*/  NGENE_INT_ENABLE ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  event_tasklet ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int,int) ; 
 int ngreadl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngwritel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void ngene_init(struct ngene *dev)
{
	struct device *pdev = &dev->pci_dev->dev;
	int i;

	tasklet_init(&dev->event_tasklet, event_tasklet, (unsigned long)dev);

	memset_io(dev->iomem + 0xc000, 0x00, 0x220);
	memset_io(dev->iomem + 0xc400, 0x00, 0x100);

	for (i = 0; i < MAX_STREAM; i++) {
		dev->channel[i].dev = dev;
		dev->channel[i].number = i;
	}

	dev->fw_interface_version = 0;

	ngwritel(0, NGENE_INT_ENABLE);

	dev->icounts = ngreadl(NGENE_INT_COUNTS);

	dev->device_version = ngreadl(DEV_VER) & 0x0f;
	dev_info(pdev, "Device version %d\n", dev->device_version);
}