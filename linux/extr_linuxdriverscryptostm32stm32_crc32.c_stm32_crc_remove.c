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
struct stm32_crc {int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  list; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  algs ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 TYPE_1__ crc_list ; 
 int /*<<< orphan*/  crypto_unregister_shashes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct stm32_crc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32_crc_remove(struct platform_device *pdev)
{
	struct stm32_crc *crc = platform_get_drvdata(pdev);
	int ret = pm_runtime_get_sync(crc->dev);

	if (ret < 0)
		return ret;

	spin_lock(&crc_list.lock);
	list_del(&crc->list);
	spin_unlock(&crc_list.lock);

	crypto_unregister_shashes(algs, ARRAY_SIZE(algs));

	pm_runtime_disable(crc->dev);
	pm_runtime_put_noidle(crc->dev);

	clk_disable_unprepare(crc->clk);

	return 0;
}