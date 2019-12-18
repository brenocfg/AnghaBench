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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct l2cache_pmu {int /*<<< orphan*/  num_pmus; int /*<<< orphan*/  clusters; } ;
struct device {struct device* parent; } ;
struct cluster_pmu {unsigned long cluster_id; int irq; int on_cpu; int /*<<< orphan*/  pmu_lock; struct l2cache_pmu* l2cache_pmu; int /*<<< orphan*/  next; } ;
struct TYPE_2__ {int /*<<< orphan*/  unique_id; } ;
struct acpi_device {TYPE_1__ pnp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IRQF_NOBALANCING ; 
 int IRQF_NO_THREAD ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned long) ; 
 struct cluster_pmu* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,char*,struct cluster_pmu*) ; 
 int /*<<< orphan*/  irq_set_status_flags (int,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (int /*<<< orphan*/ ,int,unsigned long*) ; 
 int /*<<< orphan*/  l2_cache_handle_irq ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int l2_cache_pmu_probe_cluster(struct device *dev, void *data)
{
	struct platform_device *pdev = to_platform_device(dev->parent);
	struct platform_device *sdev = to_platform_device(dev);
	struct l2cache_pmu *l2cache_pmu = data;
	struct cluster_pmu *cluster;
	struct acpi_device *device;
	unsigned long fw_cluster_id;
	int err;
	int irq;

	if (acpi_bus_get_device(ACPI_HANDLE(dev), &device))
		return -ENODEV;

	if (kstrtoul(device->pnp.unique_id, 10, &fw_cluster_id) < 0) {
		dev_err(&pdev->dev, "unable to read ACPI uid\n");
		return -ENODEV;
	}

	cluster = devm_kzalloc(&pdev->dev, sizeof(*cluster), GFP_KERNEL);
	if (!cluster)
		return -ENOMEM;

	INIT_LIST_HEAD(&cluster->next);
	list_add(&cluster->next, &l2cache_pmu->clusters);
	cluster->cluster_id = fw_cluster_id;

	irq = platform_get_irq(sdev, 0);
	if (irq < 0)
		return irq;
	irq_set_status_flags(irq, IRQ_NOAUTOEN);
	cluster->irq = irq;

	cluster->l2cache_pmu = l2cache_pmu;
	cluster->on_cpu = -1;

	err = devm_request_irq(&pdev->dev, irq, l2_cache_handle_irq,
			       IRQF_NOBALANCING | IRQF_NO_THREAD,
			       "l2-cache-pmu", cluster);
	if (err) {
		dev_err(&pdev->dev,
			"Unable to request IRQ%d for L2 PMU counters\n", irq);
		return err;
	}

	dev_info(&pdev->dev,
		"Registered L2 cache PMU cluster %ld\n", fw_cluster_id);

	spin_lock_init(&cluster->pmu_lock);

	l2cache_pmu->num_pmus++;

	return 0;
}