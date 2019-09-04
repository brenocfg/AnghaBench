#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_11__ {int index; unsigned long mem_offset; unsigned long io_offset; TYPE_2__* io_resource; TYPE_1__* mem_resource; int /*<<< orphan*/ * pci_ops; } ;
struct TYPE_8__ {char* name; unsigned long start; unsigned long end; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {char* name; unsigned long end; int /*<<< orphan*/  flags; scalar_t__ start; } ;
struct bridge_controller {int widget_id; int baddr; int* pci_int; TYPE_5__ pc; TYPE_4__* base; int /*<<< orphan*/  nasid; int /*<<< orphan*/  irq_cpu; TYPE_2__ io; TYPE_1__ mem; } ;
typedef  int /*<<< orphan*/  nasid_t ;
struct TYPE_10__ {int b_int_device; int b_wid_control; int b_wid_int_upper; int b_wid_int_lower; int b_dir_map; int /*<<< orphan*/  b_wid_tflush; TYPE_3__* b_device; scalar_t__ b_int_enable; int /*<<< orphan*/  b_int_rst_stat; } ;
typedef  TYPE_4__ bridge_t ;
struct TYPE_12__ {unsigned long end; } ;
struct TYPE_9__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int BRIDGE_CTRL_IO_SWAP ; 
 int BRIDGE_CTRL_MEM_SWAP ; 
 int BRIDGE_CTRL_PAGE_SIZE ; 
 int /*<<< orphan*/  BRIDGE_DEV_SWAP_DIR ; 
 int /*<<< orphan*/  BRIDGE_IRR_ALL_CLR ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 unsigned long NODE_OFFSET (int /*<<< orphan*/ ) ; 
 int PCI64_ATTR_BAR ; 
 int /*<<< orphan*/  PCI_PROBE_ONLY ; 
 scalar_t__ RAW_NODE_SWIN_BASE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bridge_pci_ops ; 
 struct bridge_controller* bridges ; 
 TYPE_6__ ioport_resource ; 
 int /*<<< orphan*/  pci_set_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  register_pci_controller (TYPE_5__*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

int bridge_probe(nasid_t nasid, int widget_id, int masterwid)
{
	unsigned long offset = NODE_OFFSET(nasid);
	struct bridge_controller *bc;
	static int num_bridges = 0;
	bridge_t *bridge;
	int slot;

	pci_set_flags(PCI_PROBE_ONLY);

	printk("a bridge\n");

	/* XXX: kludge alert.. */
	if (!num_bridges)
		ioport_resource.end = ~0UL;

	bc = &bridges[num_bridges];

	bc->pc.pci_ops		= &bridge_pci_ops;
	bc->pc.mem_resource	= &bc->mem;
	bc->pc.io_resource	= &bc->io;

	bc->pc.index		= num_bridges;

	bc->mem.name		= "Bridge PCI MEM";
	bc->pc.mem_offset	= offset;
	bc->mem.start		= 0;
	bc->mem.end		= ~0UL;
	bc->mem.flags		= IORESOURCE_MEM;

	bc->io.name		= "Bridge IO MEM";
	bc->pc.io_offset	= offset;
	bc->io.start		= 0UL;
	bc->io.end		= ~0UL;
	bc->io.flags		= IORESOURCE_IO;

	bc->irq_cpu = smp_processor_id();
	bc->widget_id = widget_id;
	bc->nasid = nasid;

	bc->baddr = (u64)masterwid << 60 | PCI64_ATTR_BAR;

	/*
	 * point to this bridge
	 */
	bridge = (bridge_t *) RAW_NODE_SWIN_BASE(nasid, widget_id);

	/*
	 * Clear all pending interrupts.
	 */
	bridge->b_int_rst_stat = BRIDGE_IRR_ALL_CLR;

	/*
	 * Until otherwise set up, assume all interrupts are from slot 0
	 */
	bridge->b_int_device = 0x0;

	/*
	 * swap pio's to pci mem and io space (big windows)
	 */
	bridge->b_wid_control |= BRIDGE_CTRL_IO_SWAP |
				 BRIDGE_CTRL_MEM_SWAP;
#ifdef CONFIG_PAGE_SIZE_4KB
	bridge->b_wid_control &= ~BRIDGE_CTRL_PAGE_SIZE;
#else /* 16kB or larger */
	bridge->b_wid_control |= BRIDGE_CTRL_PAGE_SIZE;
#endif

	/*
	 * Hmm...  IRIX sets additional bits in the address which
	 * are documented as reserved in the bridge docs.
	 */
	bridge->b_wid_int_upper = 0x8000 | (masterwid << 16);
	bridge->b_wid_int_lower = 0x01800090;	/* PI_INT_PEND_MOD off*/
	bridge->b_dir_map = (masterwid << 20);	/* DMA */
	bridge->b_int_enable = 0;

	for (slot = 0; slot < 8; slot ++) {
		bridge->b_device[slot].reg |= BRIDGE_DEV_SWAP_DIR;
		bc->pci_int[slot] = -1;
	}
	bridge->b_wid_tflush;	  /* wait until Bridge PIO complete */

	bc->base = bridge;

	register_pci_controller(&bc->pc);

	num_bridges++;

	return 0;
}