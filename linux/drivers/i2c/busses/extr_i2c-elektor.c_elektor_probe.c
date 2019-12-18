#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/  base_iomem ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ i2c_pcf_add_bus (TYPE_2__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioport_unmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 scalar_t__ irq ; 
 int /*<<< orphan*/  mmapped ; 
 scalar_t__ pcf_isa_init () ; 
 TYPE_2__ pcf_isa_ops ; 
 int /*<<< orphan*/  pcf_wait ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int elektor_probe(struct device *dev, unsigned int id)
{
	init_waitqueue_head(&pcf_wait);
	if (pcf_isa_init())
		return -ENODEV;
	pcf_isa_ops.dev.parent = dev;
	if (i2c_pcf_add_bus(&pcf_isa_ops) < 0)
		goto fail;

	dev_info(dev, "found device at %#x\n", base);

	return 0;

 fail:
	if (irq > 0) {
		disable_irq(irq);
		free_irq(irq, NULL);
	}

	if (!mmapped) {
		ioport_unmap(base_iomem);
		release_region(base, 2);
	} else {
		iounmap(base_iomem);
		release_mem_region(base, 2);
	}
	return -ENODEV;
}