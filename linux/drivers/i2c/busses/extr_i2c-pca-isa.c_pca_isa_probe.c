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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_clock; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IO_SIZE ; 
 int /*<<< orphan*/  base ; 
 scalar_t__ check_legacy_ioport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_irq (int,int /*<<< orphan*/ *) ; 
 scalar_t__ i2c_pca_add_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int irq ; 
 int /*<<< orphan*/  pca_handler ; 
 TYPE_1__ pca_isa_data ; 
 int /*<<< orphan*/  pca_isa_ops ; 
 int /*<<< orphan*/  pca_wait ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int pca_isa_probe(struct device *dev, unsigned int id)
{
	init_waitqueue_head(&pca_wait);

	dev_info(dev, "i/o base %#08lx. irq %d\n", base, irq);

#ifdef CONFIG_PPC
	if (check_legacy_ioport(base)) {
		dev_err(dev, "I/O address %#08lx is not available\n", base);
		goto out;
	}
#endif

	if (!request_region(base, IO_SIZE, "i2c-pca-isa")) {
		dev_err(dev, "I/O address %#08lx is in use\n", base);
		goto out;
	}

	if (irq > -1) {
		if (request_irq(irq, pca_handler, 0, "i2c-pca-isa", &pca_isa_ops) < 0) {
			dev_err(dev, "Request irq%d failed\n", irq);
			goto out_region;
		}
	}

	pca_isa_data.i2c_clock = clock;
	if (i2c_pca_add_bus(&pca_isa_ops) < 0) {
		dev_err(dev, "Failed to add i2c bus\n");
		goto out_irq;
	}

	return 0;

 out_irq:
	if (irq > -1)
		free_irq(irq, &pca_isa_ops);
 out_region:
	release_region(base, IO_SIZE);
 out:
	return -ENODEV;
}