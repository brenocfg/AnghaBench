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
struct pnp_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ACPI_COMPATIBILITY 134 
#define  ACPI_TRANSFER_16 133 
#define  ACPI_TRANSFER_8 132 
#define  ACPI_TRANSFER_8_16 131 
#define  ACPI_TYPE_A 130 
#define  ACPI_TYPE_B 129 
#define  ACPI_TYPE_F 128 
 int IORESOURCE_DMA_16BIT ; 
 int IORESOURCE_DMA_8AND16BIT ; 
 int IORESOURCE_DMA_8BIT ; 
 int IORESOURCE_DMA_COMPATIBLE ; 
 int IORESOURCE_DMA_MASTER ; 
 int IORESOURCE_DMA_TYPEA ; 
 int IORESOURCE_DMA_TYPEB ; 
 int IORESOURCE_DMA_TYPEF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int dma_flags(struct pnp_dev *dev, int type, int bus_master,
		     int transfer)
{
	int flags = 0;

	if (bus_master)
		flags |= IORESOURCE_DMA_MASTER;
	switch (type) {
	case ACPI_COMPATIBILITY:
		flags |= IORESOURCE_DMA_COMPATIBLE;
		break;
	case ACPI_TYPE_A:
		flags |= IORESOURCE_DMA_TYPEA;
		break;
	case ACPI_TYPE_B:
		flags |= IORESOURCE_DMA_TYPEB;
		break;
	case ACPI_TYPE_F:
		flags |= IORESOURCE_DMA_TYPEF;
		break;
	default:
		/* Set a default value ? */
		flags |= IORESOURCE_DMA_COMPATIBLE;
		dev_err(&dev->dev, "invalid DMA type %d\n", type);
	}
	switch (transfer) {
	case ACPI_TRANSFER_8:
		flags |= IORESOURCE_DMA_8BIT;
		break;
	case ACPI_TRANSFER_8_16:
		flags |= IORESOURCE_DMA_8AND16BIT;
		break;
	case ACPI_TRANSFER_16:
		flags |= IORESOURCE_DMA_16BIT;
		break;
	default:
		/* Set a default value ? */
		flags |= IORESOURCE_DMA_8AND16BIT;
		dev_err(&dev->dev, "invalid DMA transfer type %d\n", transfer);
	}

	return flags;
}