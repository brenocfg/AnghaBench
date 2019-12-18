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
typedef  int /*<<< orphan*/  u8 ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_msic_platform_data {int dummy; } ;
struct intel_msic {scalar_t__ vendor; int /*<<< orphan*/  version; int /*<<< orphan*/  irq_base; struct platform_device* pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTEL_MSIC_ID0 ; 
 int /*<<< orphan*/  INTEL_MSIC_ID1 ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSIC_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSIC_MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ MSIC_VENDOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSIC_VERSION (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct intel_msic_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct intel_msic* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int intel_msic_init_devices (struct intel_msic*) ; 
 int intel_scu_ipc_ioread8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct intel_msic*) ; 

__attribute__((used)) static int intel_msic_probe(struct platform_device *pdev)
{
	struct intel_msic_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct intel_msic *msic;
	struct resource *res;
	u8 id0, id1;
	int ret;

	if (!pdata) {
		dev_err(&pdev->dev, "no platform data passed\n");
		return -EINVAL;
	}

	/* First validate that we have an MSIC in place */
	ret = intel_scu_ipc_ioread8(INTEL_MSIC_ID0, &id0);
	if (ret) {
		dev_err(&pdev->dev, "failed to identify the MSIC chip (ID0)\n");
		return -ENXIO;
	}

	ret = intel_scu_ipc_ioread8(INTEL_MSIC_ID1, &id1);
	if (ret) {
		dev_err(&pdev->dev, "failed to identify the MSIC chip (ID1)\n");
		return -ENXIO;
	}

	if (MSIC_VENDOR(id0) != MSIC_VENDOR(id1)) {
		dev_err(&pdev->dev, "invalid vendor ID: %x, %x\n", id0, id1);
		return -ENXIO;
	}

	msic = devm_kzalloc(&pdev->dev, sizeof(*msic), GFP_KERNEL);
	if (!msic)
		return -ENOMEM;

	msic->vendor = MSIC_VENDOR(id0);
	msic->version = MSIC_VERSION(id0);
	msic->pdev = pdev;

	/*
	 * Map in the MSIC interrupt tree area in SRAM. This is exposed to
	 * the clients via intel_msic_irq_read().
	 */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	msic->irq_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(msic->irq_base))
		return PTR_ERR(msic->irq_base);

	platform_set_drvdata(pdev, msic);

	ret = intel_msic_init_devices(msic);
	if (ret) {
		dev_err(&pdev->dev, "failed to initialize MSIC devices\n");
		return ret;
	}

	dev_info(&pdev->dev, "Intel MSIC version %c%d (vendor %#x)\n",
		 MSIC_MAJOR(msic->version), MSIC_MINOR(msic->version),
		 msic->vendor);

	return 0;
}