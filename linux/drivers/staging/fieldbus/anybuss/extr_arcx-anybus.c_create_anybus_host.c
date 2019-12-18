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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct anybuss_ops {int host_idx; scalar_t__ irq; int /*<<< orphan*/  regmap; int /*<<< orphan*/  reset; } ;
struct anybuss_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct anybuss_host* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct anybuss_host* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_parallel_regmap (struct platform_device*,int) ; 
 struct anybuss_host* devm_anybuss_host_common_probe (int /*<<< orphan*/ *,struct anybuss_ops*) ; 
 int /*<<< orphan*/  export_reset_0 ; 
 int /*<<< orphan*/  export_reset_1 ; 
 scalar_t__ platform_get_irq (struct platform_device*,int) ; 

__attribute__((used)) static struct anybuss_host *
create_anybus_host(struct platform_device *pdev, int idx)
{
	struct anybuss_ops ops = {};

	switch (idx) {
	case 0:
		ops.reset = export_reset_0;
		break;
	case 1:
		ops.reset = export_reset_1;
		break;
	default:
		return ERR_PTR(-EINVAL);
	}
	ops.host_idx = idx;
	ops.regmap = create_parallel_regmap(pdev, idx);
	if (IS_ERR(ops.regmap))
		return ERR_CAST(ops.regmap);
	ops.irq = platform_get_irq(pdev, idx);
	if (ops.irq <= 0)
		return ERR_PTR(-EINVAL);
	return devm_anybuss_host_common_probe(&pdev->dev, &ops);
}