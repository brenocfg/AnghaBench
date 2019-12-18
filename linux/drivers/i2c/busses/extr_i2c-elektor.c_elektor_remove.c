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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/  base_iomem ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioport_unmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 scalar_t__ irq ; 
 int /*<<< orphan*/  mmapped ; 
 int /*<<< orphan*/  pcf_isa_ops ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int elektor_remove(struct device *dev, unsigned int id)
{
	i2c_del_adapter(&pcf_isa_ops);

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

	return 0;
}