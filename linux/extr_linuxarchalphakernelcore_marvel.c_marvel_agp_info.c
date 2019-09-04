#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int* vuip ;
struct pci_controller {scalar_t__ sysdata; int /*<<< orphan*/  index; int /*<<< orphan*/  sg_pci; } ;
struct io7_port {TYPE_8__* csrs; } ;
struct io7 {TYPE_1__* ports; } ;
struct TYPE_18__ {int /*<<< orphan*/  csr; } ;
struct TYPE_14__ {int /*<<< orphan*/  csr; } ;
struct TYPE_19__ {TYPE_7__ AGP_CMD; TYPE_3__ AGP_STAT; } ;
typedef  TYPE_8__ io7_ioport_csrs ;
struct TYPE_17__ {int /*<<< orphan*/  lw; } ;
struct TYPE_15__ {int rq; } ;
struct TYPE_16__ {TYPE_4__ bits; int /*<<< orphan*/  lw; } ;
struct TYPE_13__ {int /*<<< orphan*/ * sysdata; scalar_t__ size; scalar_t__ bus_base; } ;
struct TYPE_20__ {TYPE_6__ mode; TYPE_5__ capability; TYPE_2__ aperture; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * private; struct pci_controller* hose; } ;
typedef  TYPE_9__ alpha_agp_info ;
struct TYPE_12__ {struct pci_controller* hose; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IO7_AGP_PORT ; 
 int /*<<< orphan*/  PCI_DEVFN (int,int /*<<< orphan*/ ) ; 
 scalar_t__ build_conf_addr (struct pci_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marvel_agp_ops ; 
 struct io7* marvel_next_io7 (struct io7*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

alpha_agp_info *
marvel_agp_info(void)
{
	struct pci_controller *hose;
	io7_ioport_csrs *csrs;
	alpha_agp_info *agp;
	struct io7 *io7;

	/*
	 * Find the first IO7 with an AGP card.
	 *
	 * FIXME -- there should be a better way (we want to be able to
	 * specify and what if the agp card is not video???)
	 */
	hose = NULL;
	for (io7 = NULL; (io7 = marvel_next_io7(io7)) != NULL; ) {
		struct pci_controller *h;
		vuip addr;

		if (!io7->ports[IO7_AGP_PORT].enabled)
			continue;

		h = io7->ports[IO7_AGP_PORT].hose;
		addr = (vuip)build_conf_addr(h, 0, PCI_DEVFN(5, 0), 0);

		if (*addr != 0xffffffffu) {
			hose = h;
			break;
		}
	}

	if (!hose || !hose->sg_pci)
		return NULL;

	printk("MARVEL - using hose %d as AGP\n", hose->index);

	/* 
	 * Get the csrs from the hose.
	 */
	csrs = ((struct io7_port *)hose->sysdata)->csrs;

	/*
	 * Allocate the info structure.
	 */
	agp = kmalloc(sizeof(*agp), GFP_KERNEL);
	if (!agp)
		return NULL;

	/*
	 * Fill it in.
	 */
	agp->hose = hose;
	agp->private = NULL;
	agp->ops = &marvel_agp_ops;

	/*
	 * Aperture - not configured until ops.setup().
	 */
	agp->aperture.bus_base = 0;
	agp->aperture.size = 0;
	agp->aperture.sysdata = NULL;

	/*
	 * Capabilities.
	 *
	 * NOTE: IO7 reports through AGP_STAT that it can support a read queue
	 *       depth of 17 (rq = 0x10). It actually only supports a depth of
	 * 	 16 (rq = 0xf).
	 */
	agp->capability.lw = csrs->AGP_STAT.csr;
	agp->capability.bits.rq = 0xf;
	
	/*
	 * Mode.
	 */
	agp->mode.lw = csrs->AGP_CMD.csr;

	return agp;
}