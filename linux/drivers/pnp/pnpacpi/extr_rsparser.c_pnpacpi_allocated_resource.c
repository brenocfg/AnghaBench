#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct resource {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
struct resource_win {struct resource res; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
struct pnp_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  data; int /*<<< orphan*/  capabilities; } ;
struct acpi_resource_vendor_typed {int dummy; } ;
struct acpi_resource_gpio {int /*<<< orphan*/  shareable; int /*<<< orphan*/  polarity; int /*<<< orphan*/  triggering; } ;
struct acpi_resource_dma {int /*<<< orphan*/ * channels; int /*<<< orphan*/  transfer; int /*<<< orphan*/  bus_master; int /*<<< orphan*/  type; int /*<<< orphan*/  channel_count; } ;
struct TYPE_4__ {struct acpi_resource_vendor_typed vendor_typed; struct acpi_resource_dma dma; } ;
struct acpi_resource {int type; TYPE_2__ data; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
#define  ACPI_RESOURCE_TYPE_DMA 139 
#define  ACPI_RESOURCE_TYPE_END_DEPENDENT 138 
#define  ACPI_RESOURCE_TYPE_END_TAG 137 
#define  ACPI_RESOURCE_TYPE_FIXED_IO 136 
#define  ACPI_RESOURCE_TYPE_FIXED_MEMORY32 135 
#define  ACPI_RESOURCE_TYPE_GENERIC_REGISTER 134 
#define  ACPI_RESOURCE_TYPE_IO 133 
#define  ACPI_RESOURCE_TYPE_MEMORY24 132 
#define  ACPI_RESOURCE_TYPE_MEMORY32 131 
#define  ACPI_RESOURCE_TYPE_SERIAL_BUS 130 
#define  ACPI_RESOURCE_TYPE_START_DEPENDENT 129 
#define  ACPI_RESOURCE_TYPE_VENDOR 128 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int IORESOURCE_DISABLED ; 
 int /*<<< orphan*/  PNP_WRITE ; 
 int acpi_dev_gpio_irq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int acpi_dev_irq_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_dev_resource_address_space (struct acpi_resource*,struct resource_win*) ; 
 scalar_t__ acpi_dev_resource_ext_address_space (struct acpi_resource*,struct resource_win*) ; 
 scalar_t__ acpi_dev_resource_interrupt (struct acpi_resource*,int,struct resource*) ; 
 int /*<<< orphan*/  acpi_dev_resource_io (struct acpi_resource*,struct resource*) ; 
 int /*<<< orphan*/  acpi_dev_resource_memory (struct acpi_resource*,struct resource*) ; 
 scalar_t__ acpi_gpio_get_irq_resource (struct acpi_resource*,struct acpi_resource_gpio**) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int dma_flags (struct pnp_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_add_dma_resource (struct pnp_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pnp_add_irq_resource (struct pnp_dev*,int,int) ; 
 int /*<<< orphan*/  pnp_add_resource (struct pnp_dev*,struct resource*) ; 
 scalar_t__ pnp_can_write (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnpacpi_add_irqresource (struct pnp_dev*,struct resource*) ; 
 int /*<<< orphan*/  pnpacpi_parse_allocated_vendor (struct pnp_dev*,struct acpi_resource_vendor_typed*) ; 

__attribute__((used)) static acpi_status pnpacpi_allocated_resource(struct acpi_resource *res,
					      void *data)
{
	struct pnp_dev *dev = data;
	struct acpi_resource_dma *dma;
	struct acpi_resource_vendor_typed *vendor_typed;
	struct acpi_resource_gpio *gpio;
	struct resource_win win = {{0}, 0};
	struct resource *r = &win.res;
	int i, flags;

	if (acpi_dev_resource_address_space(res, &win)
	    || acpi_dev_resource_ext_address_space(res, &win)) {
		pnp_add_resource(dev, &win.res);
		return AE_OK;
	}

	r->flags = 0;
	if (acpi_dev_resource_interrupt(res, 0, r)) {
		pnpacpi_add_irqresource(dev, r);
		for (i = 1; acpi_dev_resource_interrupt(res, i, r); i++)
			pnpacpi_add_irqresource(dev, r);

		if (i > 1) {
			/*
			 * The IRQ encoder puts a single interrupt in each
			 * descriptor, so if a _CRS descriptor has more than
			 * one interrupt, we won't be able to re-encode it.
			 */
			if (pnp_can_write(dev)) {
				dev_warn(&dev->dev,
					 "multiple interrupts in _CRS descriptor; configuration can't be changed\n");
				dev->capabilities &= ~PNP_WRITE;
			}
		}
		return AE_OK;
	} else if (acpi_gpio_get_irq_resource(res, &gpio)) {
		/*
		 * If the resource is GpioInt() type then extract the IRQ
		 * from GPIO resource and fill it into IRQ resource type.
		 */
		i = acpi_dev_gpio_irq_get(dev->data, 0);
		if (i >= 0) {
			flags = acpi_dev_irq_flags(gpio->triggering,
						   gpio->polarity,
						   gpio->shareable);
		} else {
			flags = IORESOURCE_DISABLED;
		}
		pnp_add_irq_resource(dev, i, flags);
		return AE_OK;
	} else if (r->flags & IORESOURCE_DISABLED) {
		pnp_add_irq_resource(dev, 0, IORESOURCE_DISABLED);
		return AE_OK;
	}

	switch (res->type) {
	case ACPI_RESOURCE_TYPE_MEMORY24:
	case ACPI_RESOURCE_TYPE_MEMORY32:
	case ACPI_RESOURCE_TYPE_FIXED_MEMORY32:
		if (acpi_dev_resource_memory(res, r))
			pnp_add_resource(dev, r);
		break;
	case ACPI_RESOURCE_TYPE_IO:
	case ACPI_RESOURCE_TYPE_FIXED_IO:
		if (acpi_dev_resource_io(res, r))
			pnp_add_resource(dev, r);
		break;
	case ACPI_RESOURCE_TYPE_DMA:
		dma = &res->data.dma;
		if (dma->channel_count > 0 && dma->channels[0] != (u8) -1)
			flags = dma_flags(dev, dma->type, dma->bus_master,
					  dma->transfer);
		else
			flags = IORESOURCE_DISABLED;
		pnp_add_dma_resource(dev, dma->channels[0], flags);
		break;

	case ACPI_RESOURCE_TYPE_START_DEPENDENT:
	case ACPI_RESOURCE_TYPE_END_DEPENDENT:
		break;

	case ACPI_RESOURCE_TYPE_VENDOR:
		vendor_typed = &res->data.vendor_typed;
		pnpacpi_parse_allocated_vendor(dev, vendor_typed);
		break;

	case ACPI_RESOURCE_TYPE_END_TAG:
		break;

	case ACPI_RESOURCE_TYPE_GENERIC_REGISTER:
		break;

	case ACPI_RESOURCE_TYPE_SERIAL_BUS:
		/* serial bus connections (I2C/SPI/UART) are not pnp */
		break;

	default:
		dev_warn(&dev->dev, "unknown resource type %d in _CRS\n",
			 res->type);
		return AE_ERROR;
	}

	return AE_OK;
}