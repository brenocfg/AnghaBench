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
typedef  int u32 ;
struct resource {int start; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ ITE_887x_INTCBAR ; 
 int /*<<< orphan*/  ITE_887x_IOSIZE ; 
 scalar_t__ ITE_887x_MISCR ; 
 scalar_t__ ITE_887x_POSIO0 ; 
 short const ITE_887x_POSIO_ENABLE ; 
 short const ITE_887x_POSIO_IOSIZE_32 ; 
 short const ITE_887x_POSIO_IOSIZE_8 ; 
 short const ITE_887x_POSIO_SPEED ; 
 scalar_t__ ITE_887x_PS0BAR ; 
 scalar_t__ ITE_887x_UARTBAR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int inb (short const) ; 
 int /*<<< orphan*/  moan_device (char*,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,short const) ; 
 int /*<<< orphan*/  release_region (int,int /*<<< orphan*/ ) ; 
 struct resource* request_region (short const,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int pci_ite887x_init(struct pci_dev *dev)
{
	/* inta_addr are the configuration addresses of the ITE */
	static const short inta_addr[] = { 0x2a0, 0x2c0, 0x220, 0x240, 0x1e0,
							0x200, 0x280, 0 };
	int ret, i, type;
	struct resource *iobase = NULL;
	u32 miscr, uartbar, ioport;

	/* search for the base-ioport */
	i = 0;
	while (inta_addr[i] && iobase == NULL) {
		iobase = request_region(inta_addr[i], ITE_887x_IOSIZE,
								"ite887x");
		if (iobase != NULL) {
			/* write POSIO0R - speed | size | ioport */
			pci_write_config_dword(dev, ITE_887x_POSIO0,
				ITE_887x_POSIO_ENABLE | ITE_887x_POSIO_SPEED |
				ITE_887x_POSIO_IOSIZE_32 | inta_addr[i]);
			/* write INTCBAR - ioport */
			pci_write_config_dword(dev, ITE_887x_INTCBAR,
								inta_addr[i]);
			ret = inb(inta_addr[i]);
			if (ret != 0xff) {
				/* ioport connected */
				break;
			}
			release_region(iobase->start, ITE_887x_IOSIZE);
			iobase = NULL;
		}
		i++;
	}

	if (!inta_addr[i]) {
		dev_err(&dev->dev, "ite887x: could not find iobase\n");
		return -ENODEV;
	}

	/* start of undocumented type checking (see parport_pc.c) */
	type = inb(iobase->start + 0x18) & 0x0f;

	switch (type) {
	case 0x2:	/* ITE8871 (1P) */
	case 0xa:	/* ITE8875 (1P) */
		ret = 0;
		break;
	case 0xe:	/* ITE8872 (2S1P) */
		ret = 2;
		break;
	case 0x6:	/* ITE8873 (1S) */
		ret = 1;
		break;
	case 0x8:	/* ITE8874 (2S) */
		ret = 2;
		break;
	default:
		moan_device("Unknown ITE887x", dev);
		ret = -ENODEV;
	}

	/* configure all serial ports */
	for (i = 0; i < ret; i++) {
		/* read the I/O port from the device */
		pci_read_config_dword(dev, ITE_887x_PS0BAR + (0x4 * (i + 1)),
								&ioport);
		ioport &= 0x0000FF00;	/* the actual base address */
		pci_write_config_dword(dev, ITE_887x_POSIO0 + (0x4 * (i + 1)),
			ITE_887x_POSIO_ENABLE | ITE_887x_POSIO_SPEED |
			ITE_887x_POSIO_IOSIZE_8 | ioport);

		/* write the ioport to the UARTBAR */
		pci_read_config_dword(dev, ITE_887x_UARTBAR, &uartbar);
		uartbar &= ~(0xffff << (16 * i));	/* clear half the reg */
		uartbar |= (ioport << (16 * i));	/* set the ioport */
		pci_write_config_dword(dev, ITE_887x_UARTBAR, uartbar);

		/* get current config */
		pci_read_config_dword(dev, ITE_887x_MISCR, &miscr);
		/* disable interrupts (UARTx_Routing[3:0]) */
		miscr &= ~(0xf << (12 - 4 * i));
		/* activate the UART (UARTx_En) */
		miscr |= 1 << (23 - i);
		/* write new config with activated UART */
		pci_write_config_dword(dev, ITE_887x_MISCR, miscr);
	}

	if (ret <= 0) {
		/* the device has no UARTs if we get here */
		release_region(iobase->start, ITE_887x_IOSIZE);
	}

	return ret;
}