#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_MBOX_BITS ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DB8500_PRCMU_FW_VERSION_OFFSET ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ESRAM0_DEEP_SLEEP_STATE_RET ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_NO_SUSPEND ; 
 int /*<<< orphan*/  PRCM_ARM_IT1_CLR ; 
 int /*<<< orphan*/  common_prcmu_devs ; 
 int /*<<< orphan*/  db8500_irq_domain ; 
 int /*<<< orphan*/  db8500_irq_init (struct device_node*) ; 
 int /*<<< orphan*/  db8500_prcmu_devs ; 
 int db8500_prcmu_register_ab8500 (TYPE_1__*) ; 
 int /*<<< orphan*/  dbx500_fw_version_init (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 void* devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_prcm_registers () ; 
 int mfd_add_devices (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfd_remove_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  of_machine_is_compatible (char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 void* prcmu_base ; 
 int /*<<< orphan*/  prcmu_config_esram0_deep_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prcmu_irq_handler ; 
 int /*<<< orphan*/  prcmu_irq_thread_fn ; 
 int request_threaded_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 void* tcdm_base ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db8500_prcmu_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	int irq = 0, err = 0;
	struct resource *res;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "prcmu");
	if (!res) {
		dev_err(&pdev->dev, "no prcmu memory region provided\n");
		return -EINVAL;
	}
	prcmu_base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (!prcmu_base) {
		dev_err(&pdev->dev,
			"failed to ioremap prcmu register memory\n");
		return -ENOMEM;
	}
	init_prcm_registers();
	dbx500_fw_version_init(pdev, DB8500_PRCMU_FW_VERSION_OFFSET);
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "prcmu-tcdm");
	if (!res) {
		dev_err(&pdev->dev, "no prcmu tcdm region provided\n");
		return -EINVAL;
	}
	tcdm_base = devm_ioremap(&pdev->dev, res->start,
			resource_size(res));
	if (!tcdm_base) {
		dev_err(&pdev->dev,
			"failed to ioremap prcmu-tcdm register memory\n");
		return -ENOMEM;
	}

	/* Clean up the mailbox interrupts after pre-kernel code. */
	writel(ALL_MBOX_BITS, PRCM_ARM_IT1_CLR);

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return irq;

	err = request_threaded_irq(irq, prcmu_irq_handler,
	        prcmu_irq_thread_fn, IRQF_NO_SUSPEND, "prcmu", NULL);
	if (err < 0) {
		pr_err("prcmu: Failed to allocate IRQ_DB8500_PRCMU1.\n");
		return err;
	}

	db8500_irq_init(np);

	prcmu_config_esram0_deep_sleep(ESRAM0_DEEP_SLEEP_STATE_RET);

	err = mfd_add_devices(&pdev->dev, 0, common_prcmu_devs,
			      ARRAY_SIZE(common_prcmu_devs), NULL, 0, db8500_irq_domain);
	if (err) {
		pr_err("prcmu: Failed to add subdevices\n");
		return err;
	}

	/* TODO: Remove restriction when clk definitions are available. */
	if (!of_machine_is_compatible("st-ericsson,u8540")) {
		err = mfd_add_devices(&pdev->dev, 0, db8500_prcmu_devs,
				      ARRAY_SIZE(db8500_prcmu_devs), NULL, 0,
				      db8500_irq_domain);
		if (err) {
			mfd_remove_devices(&pdev->dev);
			pr_err("prcmu: Failed to add subdevices\n");
			return err;
		}
	}

	err = db8500_prcmu_register_ab8500(&pdev->dev);
	if (err) {
		mfd_remove_devices(&pdev->dev);
		pr_err("prcmu: Failed to add ab8500 subdevice\n");
		return err;
	}

	pr_info("DB8500 PRCMU initialized\n");
	return err;
}