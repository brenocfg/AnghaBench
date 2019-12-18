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
struct net_device {int dummy; } ;
struct el3_private {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  EL3WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EL3_IO_EXTENT ; 
 int /*<<< orphan*/  EL3_ISA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 scalar_t__ WN0_IRQ ; 
 struct net_device* alloc_etherdev (int) ; 
 int current_tag ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct net_device*) ; 
 size_t el3_cards ; 
 scalar_t__ el3_common_init (struct net_device*) ; 
 int /*<<< orphan*/  el3_dev_fill (struct net_device*,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 struct net_device** el3_devs ; 
 int el3_isa_id_sequence (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  id_port ; 
 int id_read_eeprom (int) ; 
 int inw (int) ; 
 int* irq ; 
 int /*<<< orphan*/  netdev_boot_setup_check (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  request_region (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int el3_isa_match(struct device *pdev, unsigned int ndev)
{
	struct net_device *dev;
	int ioaddr, isa_irq, if_port, err;
	unsigned int iobase;
	__be16 phys_addr[3];

	while ((err = el3_isa_id_sequence(phys_addr)) == 2)
		;	/* Skip to next card when PnP card found */
	if (err == 1)
		return 0;

	iobase = id_read_eeprom(8);
	if_port = iobase >> 14;
	ioaddr = 0x200 + ((iobase & 0x1f) << 4);
	if (irq[el3_cards] > 1 && irq[el3_cards] < 16)
		isa_irq = irq[el3_cards];
	else
		isa_irq = id_read_eeprom(9) >> 12;

	dev = alloc_etherdev(sizeof(struct el3_private));
	if (!dev)
		return -ENOMEM;

	SET_NETDEV_DEV(dev, pdev);
	netdev_boot_setup_check(dev);

	if (!request_region(ioaddr, EL3_IO_EXTENT, "3c509-isa")) {
		free_netdev(dev);
		return 0;
	}

	/* Set the adaptor tag so that the next card can be found. */
	outb(0xd0 + ++current_tag, id_port);

	/* Activate the adaptor at the EEPROM location. */
	outb((ioaddr >> 4) | 0xe0, id_port);

	EL3WINDOW(0);
	if (inw(ioaddr) != 0x6d50) {
		free_netdev(dev);
		return 0;
	}

	/* Free the interrupt so that some other card can use it. */
	outw(0x0f00, ioaddr + WN0_IRQ);

	el3_dev_fill(dev, phys_addr, ioaddr, isa_irq, if_port, EL3_ISA);
	dev_set_drvdata(pdev, dev);
	if (el3_common_init(dev)) {
		free_netdev(dev);
		return 0;
	}

	el3_devs[el3_cards++] = dev;
	return 1;
}