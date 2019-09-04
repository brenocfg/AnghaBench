#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct hwspinlock* lock; } ;
struct sprd_hwspinlock_dev {scalar_t__ clk; TYPE_3__ bank; scalar_t__ base; } ;
struct resource {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct hwspinlock {scalar_t__ priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HWSPINLOCK_RECCTRL ; 
 scalar_t__ HWSPINLOCK_TOKEN (int) ; 
 int /*<<< orphan*/  HWSPINLOCK_USER_BITS ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int SPRD_HWLOCKS_NUM ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 scalar_t__ devm_clk_get (TYPE_1__*,char*) ; 
 scalar_t__ devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct sprd_hwspinlock_dev* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int hwspin_lock_register (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sprd_hwspinlock_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  sprd_hwspinlock_ops ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sprd_hwspinlock_probe(struct platform_device *pdev)
{
	struct sprd_hwspinlock_dev *sprd_hwlock;
	struct hwspinlock *lock;
	struct resource *res;
	int i, ret;

	if (!pdev->dev.of_node)
		return -ENODEV;

	sprd_hwlock = devm_kzalloc(&pdev->dev,
				   sizeof(struct sprd_hwspinlock_dev) +
				   SPRD_HWLOCKS_NUM * sizeof(*lock),
				   GFP_KERNEL);
	if (!sprd_hwlock)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	sprd_hwlock->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(sprd_hwlock->base))
		return PTR_ERR(sprd_hwlock->base);

	sprd_hwlock->clk = devm_clk_get(&pdev->dev, "enable");
	if (IS_ERR(sprd_hwlock->clk)) {
		dev_err(&pdev->dev, "get hwspinlock clock failed!\n");
		return PTR_ERR(sprd_hwlock->clk);
	}

	clk_prepare_enable(sprd_hwlock->clk);

	/* set the hwspinlock to record user id to identify subsystems */
	writel(HWSPINLOCK_USER_BITS, sprd_hwlock->base + HWSPINLOCK_RECCTRL);

	for (i = 0; i < SPRD_HWLOCKS_NUM; i++) {
		lock = &sprd_hwlock->bank.lock[i];
		lock->priv = sprd_hwlock->base + HWSPINLOCK_TOKEN(i);
	}

	platform_set_drvdata(pdev, sprd_hwlock);
	pm_runtime_enable(&pdev->dev);

	ret = hwspin_lock_register(&sprd_hwlock->bank, &pdev->dev,
				   &sprd_hwspinlock_ops, 0, SPRD_HWLOCKS_NUM);
	if (ret) {
		pm_runtime_disable(&pdev->dev);
		clk_disable_unprepare(sprd_hwlock->clk);
		return ret;
	}

	return 0;
}