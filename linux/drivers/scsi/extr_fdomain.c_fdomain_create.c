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
struct fdomain {int base; int chip; int /*<<< orphan*/  work; } ;
struct device {TYPE_1__* bus; } ;
struct Scsi_Host {int this_id; int irq; int io_port; int /*<<< orphan*/  n_io_port; } ;
typedef  enum chip_type { ____Placeholder_chip_type } chip_type ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDOMAIN_REGION_SIZE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long IRQF_SHARED ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 int fdomain_identify (int) ; 
 int /*<<< orphan*/  fdomain_irq ; 
 int /*<<< orphan*/  fdomain_reset (int) ; 
 int /*<<< orphan*/  fdomain_template ; 
 scalar_t__ fdomain_test_loopback (int) ; 
 int /*<<< orphan*/  fdomain_work ; 
 int /*<<< orphan*/  free_irq (int,struct fdomain*) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,unsigned long,char*,struct fdomain*) ; 
 scalar_t__ scsi_add_host (struct Scsi_Host*,struct device*) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,char*,int,int,int) ; 
 struct fdomain* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

struct Scsi_Host *fdomain_create(int base, int irq, int this_id,
				 struct device *dev)
{
	struct Scsi_Host *sh;
	struct fdomain *fd;
	enum chip_type chip;
	static const char * const chip_names[] = {
		"Unknown", "TMC-1800", "TMC-18C50", "TMC-18C30"
	};
	unsigned long irq_flags = 0;

	chip = fdomain_identify(base);
	if (!chip)
		return NULL;

	fdomain_reset(base);

	if (fdomain_test_loopback(base))
		return NULL;

	if (!irq) {
		dev_err(dev, "card has no IRQ assigned");
		return NULL;
	}

	sh = scsi_host_alloc(&fdomain_template, sizeof(struct fdomain));
	if (!sh)
		return NULL;

	if (this_id)
		sh->this_id = this_id & 0x07;

	sh->irq = irq;
	sh->io_port = base;
	sh->n_io_port = FDOMAIN_REGION_SIZE;

	fd = shost_priv(sh);
	fd->base = base;
	fd->chip = chip;
	INIT_WORK(&fd->work, fdomain_work);

	if (dev_is_pci(dev) || !strcmp(dev->bus->name, "pcmcia"))
		irq_flags = IRQF_SHARED;

	if (request_irq(irq, fdomain_irq, irq_flags, "fdomain", fd))
		goto fail_put;

	shost_printk(KERN_INFO, sh, "%s chip at 0x%x irq %d SCSI ID %d\n",
		     dev_is_pci(dev) ? "TMC-36C70 (PCI bus)" : chip_names[chip],
		     base, irq, sh->this_id);

	if (scsi_add_host(sh, dev))
		goto fail_free_irq;

	scsi_scan_host(sh);

	return sh;

fail_free_irq:
	free_irq(irq, fd);
fail_put:
	scsi_host_put(sh);
	return NULL;
}