#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/ * write_isac_fifo; int /*<<< orphan*/ * read_isac_fifo; int /*<<< orphan*/ * write_isac; int /*<<< orphan*/ * read_isac; struct fritz_adapter* priv; } ;
struct fritz_adapter {int type; int (* read_hdlc_status ) (struct fritz_adapter*,int) ;scalar_t__ io; TYPE_1__* bcs; TYPE_2__ isac; int /*<<< orphan*/  irq; int /*<<< orphan*/ * write_ctrl; int /*<<< orphan*/  hw_lock; } ;
struct TYPE_5__ {int mode; } ;

/* Variables and functions */
#define  AVM_FRITZ_PCI 130 
#define  AVM_FRITZ_PCIV2 129 
#define  AVM_FRITZ_PNP 128 
 scalar_t__ AVM_STATUS0 ; 
 int /*<<< orphan*/  AVM_STATUS0_RESET ; 
 int /*<<< orphan*/  DBG (int,char*,...) ; 
 int EBUSY ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  L1_MODE_NULL ; 
 int /*<<< orphan*/  fcpci2_init (struct fritz_adapter*) ; 
 int /*<<< orphan*/  fcpci2_irq ; 
 int /*<<< orphan*/  fcpci2_read_hdlc_status ; 
 int /*<<< orphan*/  fcpci2_read_isac ; 
 int /*<<< orphan*/  fcpci2_read_isac_fifo ; 
 int /*<<< orphan*/  fcpci2_write_ctrl ; 
 int /*<<< orphan*/  fcpci2_write_isac ; 
 int /*<<< orphan*/  fcpci2_write_isac_fifo ; 
 int /*<<< orphan*/  fcpci_init (struct fritz_adapter*) ; 
 int /*<<< orphan*/  fcpci_irq ; 
 int /*<<< orphan*/  fcpci_read_hdlc_status ; 
 int /*<<< orphan*/  fcpci_read_isac ; 
 int /*<<< orphan*/  fcpci_read_isac_fifo ; 
 int /*<<< orphan*/  fcpci_write_ctrl ; 
 int /*<<< orphan*/  fcpci_write_isac ; 
 int /*<<< orphan*/  fcpci_write_isac_fifo ; 
 int /*<<< orphan*/  fcpnp_read_hdlc_status ; 
 int /*<<< orphan*/  fcpnp_write_ctrl ; 
 int inb (scalar_t__) ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  isac_init (TYPE_2__*) ; 
 int /*<<< orphan*/  isac_setup (TYPE_2__*) ; 
 int /*<<< orphan*/  isacsx_setup (TYPE_2__*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  modehdlc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct fritz_adapter*) ; 
 int /*<<< orphan*/  request_region (scalar_t__,int,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct fritz_adapter*,int) ; 
 int stub2 (struct fritz_adapter*,int) ; 

__attribute__((used)) static int fcpcipnp_setup(struct fritz_adapter *adapter)
{
	u32 val = 0;
	int retval;

	DBG(1, "");

	isac_init(&adapter->isac); // FIXME is this okay now

	retval = -EBUSY;
	if (!request_region(adapter->io, 32, "fcpcipnp"))
		goto err;

	switch (adapter->type) {
	case AVM_FRITZ_PCIV2:
	case AVM_FRITZ_PCI:
		val = inl(adapter->io);
		break;
	case AVM_FRITZ_PNP:
		val = inb(adapter->io);
		val |= inb(adapter->io + 1) << 8;
		break;
	}

	DBG(1, "stat %#x Class %X Rev %d",
	    val, val & 0xff, (val >> 8) & 0xff);

	spin_lock_init(&adapter->hw_lock);
	adapter->isac.priv = adapter;
	switch (adapter->type) {
	case AVM_FRITZ_PCIV2:
		adapter->isac.read_isac       = &fcpci2_read_isac;
		adapter->isac.write_isac      = &fcpci2_write_isac;
		adapter->isac.read_isac_fifo  = &fcpci2_read_isac_fifo;
		adapter->isac.write_isac_fifo = &fcpci2_write_isac_fifo;

		adapter->read_hdlc_status     = &fcpci2_read_hdlc_status;
		adapter->write_ctrl           = &fcpci2_write_ctrl;
		break;
	case AVM_FRITZ_PCI:
		adapter->isac.read_isac       = &fcpci_read_isac;
		adapter->isac.write_isac      = &fcpci_write_isac;
		adapter->isac.read_isac_fifo  = &fcpci_read_isac_fifo;
		adapter->isac.write_isac_fifo = &fcpci_write_isac_fifo;

		adapter->read_hdlc_status     = &fcpci_read_hdlc_status;
		adapter->write_ctrl           = &fcpci_write_ctrl;
		break;
	case AVM_FRITZ_PNP:
		adapter->isac.read_isac       = &fcpci_read_isac;
		adapter->isac.write_isac      = &fcpci_write_isac;
		adapter->isac.read_isac_fifo  = &fcpci_read_isac_fifo;
		adapter->isac.write_isac_fifo = &fcpci_write_isac_fifo;

		adapter->read_hdlc_status     = &fcpnp_read_hdlc_status;
		adapter->write_ctrl           = &fcpnp_write_ctrl;
		break;
	}

	// Reset
	outb(0, adapter->io + AVM_STATUS0);
	mdelay(10);
	outb(AVM_STATUS0_RESET, adapter->io + AVM_STATUS0);
	mdelay(10);
	outb(0, adapter->io + AVM_STATUS0);
	mdelay(10);

	switch (adapter->type) {
	case AVM_FRITZ_PCIV2:
		retval = request_irq(adapter->irq, fcpci2_irq, IRQF_SHARED,
				     "fcpcipnp", adapter);
		break;
	case AVM_FRITZ_PCI:
		retval = request_irq(adapter->irq, fcpci_irq, IRQF_SHARED,
				     "fcpcipnp", adapter);
		break;
	case AVM_FRITZ_PNP:
		retval = request_irq(adapter->irq, fcpci_irq, 0,
				     "fcpcipnp", adapter);
		break;
	}
	if (retval)
		goto err_region;

	switch (adapter->type) {
	case AVM_FRITZ_PCIV2:
		fcpci2_init(adapter);
		isacsx_setup(&adapter->isac);
		break;
	case AVM_FRITZ_PCI:
	case AVM_FRITZ_PNP:
		fcpci_init(adapter);
		isac_setup(&adapter->isac);
		break;
	}
	val = adapter->read_hdlc_status(adapter, 0);
	DBG(0x20, "HDLC A STA %x", val);
	val = adapter->read_hdlc_status(adapter, 1);
	DBG(0x20, "HDLC B STA %x", val);

	adapter->bcs[0].mode = -1;
	adapter->bcs[1].mode = -1;
	modehdlc(&adapter->bcs[0], L1_MODE_NULL);
	modehdlc(&adapter->bcs[1], L1_MODE_NULL);

	return 0;

err_region:
	release_region(adapter->io, 32);
err:
	return retval;
}