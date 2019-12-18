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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int CFG1_IRQ_MASK ; 
 int /*<<< orphan*/  FDOMAIN_REGION_SIZE ; 
 scalar_t__ REG_CFG1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct Scsi_Host*) ; 
 struct Scsi_Host* fdomain_create (scalar_t__,int,int /*<<< orphan*/ ,struct device*) ; 
 int inb (scalar_t__) ; 
 scalar_t__* io ; 
 int* irq ; 
 int* irqs ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * scsi_id ; 

__attribute__((used)) static int fdomain_isa_param_match(struct device *dev, unsigned int ndev)
{
	struct Scsi_Host *sh;
	int irq_ = irq[ndev];

	if (!io[ndev])
		return 0;

	if (!request_region(io[ndev], FDOMAIN_REGION_SIZE, "fdomain_isa")) {
		dev_err(dev, "base 0x%x already in use", io[ndev]);
		return 0;
	}

	if (irq_ <= 0)
		irq_ = irqs[(inb(io[ndev] + REG_CFG1) & CFG1_IRQ_MASK) >> 1];

	sh = fdomain_create(io[ndev], irq_, scsi_id[ndev], dev);
	if (!sh) {
		dev_err(dev, "controller not found at base 0x%x", io[ndev]);
		release_region(io[ndev], FDOMAIN_REGION_SIZE);
		return 0;
	}

	dev_set_drvdata(dev, sh);
	return 1;
}