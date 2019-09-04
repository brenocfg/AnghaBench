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
typedef  scalar_t__ u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct ls_scfg_msi_cfg {int ibs_shift; } ;
struct ls_scfg_msi {int irqs_num; scalar_t__ msir_num; void* msir; void* used; struct ls_scfg_msi_cfg* cfg; int /*<<< orphan*/  lock; struct platform_device* pdev; int /*<<< orphan*/  msiir_addr; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 scalar_t__ BITS_TO_LONGS (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MSI_IRQS_PER_MSIR ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 void* devm_kcalloc (TYPE_1__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 struct ls_scfg_msi* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int ls_scfg_msi_domains_init (struct ls_scfg_msi*) ; 
 int /*<<< orphan*/  ls_scfg_msi_id ; 
 int /*<<< orphan*/  ls_scfg_msi_setup_hwirq (struct ls_scfg_msi*,int) ; 
 scalar_t__ msi_affinity_flag ; 
 scalar_t__ num_possible_cpus () ; 
 scalar_t__ of_irq_count (int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ls_scfg_msi*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ls_scfg_msi_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	struct ls_scfg_msi *msi_data;
	struct resource *res;
	int i, ret;

	match = of_match_device(ls_scfg_msi_id, &pdev->dev);
	if (!match)
		return -ENODEV;

	msi_data = devm_kzalloc(&pdev->dev, sizeof(*msi_data), GFP_KERNEL);
	if (!msi_data)
		return -ENOMEM;

	msi_data->cfg = (struct ls_scfg_msi_cfg *) match->data;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	msi_data->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(msi_data->regs)) {
		dev_err(&pdev->dev, "failed to initialize 'regs'\n");
		return PTR_ERR(msi_data->regs);
	}
	msi_data->msiir_addr = res->start;

	msi_data->pdev = pdev;
	spin_lock_init(&msi_data->lock);

	msi_data->irqs_num = MSI_IRQS_PER_MSIR *
			     (1 << msi_data->cfg->ibs_shift);
	msi_data->used = devm_kcalloc(&pdev->dev,
				    BITS_TO_LONGS(msi_data->irqs_num),
				    sizeof(*msi_data->used),
				    GFP_KERNEL);
	if (!msi_data->used)
		return -ENOMEM;
	/*
	 * Reserve all the hwirqs
	 * The available hwirqs will be released in ls1_msi_setup_hwirq()
	 */
	bitmap_set(msi_data->used, 0, msi_data->irqs_num);

	msi_data->msir_num = of_irq_count(pdev->dev.of_node);

	if (msi_affinity_flag) {
		u32 cpu_num;

		cpu_num = num_possible_cpus();
		if (msi_data->msir_num >= cpu_num)
			msi_data->msir_num = cpu_num;
		else
			msi_affinity_flag = 0;
	}

	msi_data->msir = devm_kcalloc(&pdev->dev, msi_data->msir_num,
				      sizeof(*msi_data->msir),
				      GFP_KERNEL);
	if (!msi_data->msir)
		return -ENOMEM;

	for (i = 0; i < msi_data->msir_num; i++)
		ls_scfg_msi_setup_hwirq(msi_data, i);

	ret = ls_scfg_msi_domains_init(msi_data);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, msi_data);

	return 0;
}