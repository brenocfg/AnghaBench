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
typedef  int u32 ;
struct pci_dev {int vendor; int device; TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 

__attribute__((used)) static void cas_program_bridge(struct pci_dev *cas_pdev)
{
	struct pci_dev *pdev = cas_pdev->bus->self;
	u32 val;

	if (!pdev)
		return;

	if (pdev->vendor != 0x8086 || pdev->device != 0x537c)
		return;

	/* Clear bit 10 (Bus Parking Control) in the Secondary
	 * Arbiter Control/Status Register which lives at offset
	 * 0x41.  Using a 32-bit word read/modify/write at 0x40
	 * is much simpler so that's how we do this.
	 */
	pci_read_config_dword(pdev, 0x40, &val);
	val &= ~0x00040000;
	pci_write_config_dword(pdev, 0x40, val);

	/* Max out the Multi-Transaction Timer settings since
	 * Cassini is the only device present.
	 *
	 * The register is 16-bit and lives at 0x50.  When the
	 * settings are enabled, it extends the GRANT# signal
	 * for a requestor after a transaction is complete.  This
	 * allows the next request to run without first needing
	 * to negotiate the GRANT# signal back.
	 *
	 * Bits 12:10 define the grant duration:
	 *
	 *	1	--	16 clocks
	 *	2	--	32 clocks
	 *	3	--	64 clocks
	 *	4	--	128 clocks
	 *	5	--	256 clocks
	 *
	 * All other values are illegal.
	 *
	 * Bits 09:00 define which REQ/GNT signal pairs get the
	 * GRANT# signal treatment.  We set them all.
	 */
	pci_write_config_word(pdev, 0x50, (5 << 10) | 0x3ff);

	/* The Read Prefecth Policy register is 16-bit and sits at
	 * offset 0x52.  It enables a "smart" pre-fetch policy.  We
	 * enable it and max out all of the settings since only one
	 * device is sitting underneath and thus bandwidth sharing is
	 * not an issue.
	 *
	 * The register has several 3 bit fields, which indicates a
	 * multiplier applied to the base amount of prefetching the
	 * chip would do.  These fields are at:
	 *
	 *	15:13	---	ReRead Primary Bus
	 *	12:10	---	FirstRead Primary Bus
	 *	09:07	---	ReRead Secondary Bus
	 *	06:04	---	FirstRead Secondary Bus
	 *
	 * Bits 03:00 control which REQ/GNT pairs the prefetch settings
	 * get enabled on.  Bit 3 is a grouped enabler which controls
	 * all of the REQ/GNT pairs from [8:3].  Bits 2 to 0 control
	 * the individual REQ/GNT pairs [2:0].
	 */
	pci_write_config_word(pdev, 0x52,
			      (0x7 << 13) |
			      (0x7 << 10) |
			      (0x7 <<  7) |
			      (0x7 <<  4) |
			      (0xf <<  0));

	/* Force cacheline size to 0x8 */
	pci_write_config_byte(pdev, PCI_CACHE_LINE_SIZE, 0x08);

	/* Force latency timer to maximum setting so Cassini can
	 * sit on the bus as long as it likes.
	 */
	pci_write_config_byte(pdev, PCI_LATENCY_TIMER, 0xff);
}