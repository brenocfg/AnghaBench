#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  flags; void* name; int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;
struct TYPE_4__ {TYPE_2__* parent; int /*<<< orphan*/  dma_parms; int /*<<< orphan*/  dma_mask; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pci_device_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_parms; int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  coherent_dma_mask; } ;
struct pci_dev {TYPE_2__ dev; int /*<<< orphan*/  irq; } ;
struct bdc_pci {struct platform_device* bdc; TYPE_2__* dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct resource*) ; 
 void* BRCM_BDC_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int /*<<< orphan*/  bdc_setup_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct bdc_pci* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_coherent_mask (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct resource*,int,int) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_end (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct bdc_pci*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_resources (struct platform_device*,struct resource*,int) ; 
 struct platform_device* platform_device_alloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static int bdc_pci_probe(struct pci_dev *pci, const struct pci_device_id *id)
{
	struct resource res[2];
	struct platform_device *bdc;
	struct bdc_pci *glue;
	int ret = -ENOMEM;

	glue = devm_kzalloc(&pci->dev, sizeof(*glue), GFP_KERNEL);
	if (!glue)
		return -ENOMEM;

	glue->dev = &pci->dev;
	ret = pci_enable_device(pci);
	if (ret) {
		dev_err(&pci->dev, "failed to enable pci device\n");
		return -ENODEV;
	}
	pci_set_master(pci);

	bdc = platform_device_alloc(BRCM_BDC_NAME, PLATFORM_DEVID_AUTO);
	if (!bdc)
		return -ENOMEM;

	memset(res, 0x00, sizeof(struct resource) * ARRAY_SIZE(res));
	bdc_setup_msi(pci);

	res[0].start	= pci_resource_start(pci, 0);
	res[0].end	= pci_resource_end(pci, 0);
	res[0].name	= BRCM_BDC_NAME;
	res[0].flags	= IORESOURCE_MEM;

	res[1].start	= pci->irq;
	res[1].name	= BRCM_BDC_NAME;
	res[1].flags	= IORESOURCE_IRQ;

	ret = platform_device_add_resources(bdc, res, ARRAY_SIZE(res));
	if (ret) {
		dev_err(&pci->dev,
			"couldn't add resources to bdc device\n");
		platform_device_put(bdc);
		return ret;
	}

	pci_set_drvdata(pci, glue);

	dma_set_coherent_mask(&bdc->dev, pci->dev.coherent_dma_mask);

	bdc->dev.dma_mask = pci->dev.dma_mask;
	bdc->dev.dma_parms = pci->dev.dma_parms;
	bdc->dev.parent = &pci->dev;
	glue->bdc = bdc;

	ret = platform_device_add(bdc);
	if (ret) {
		dev_err(&pci->dev, "failed to register bdc device\n");
		platform_device_put(bdc);
		return ret;
	}

	return 0;
}