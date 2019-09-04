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
struct sram_dev {scalar_t__ clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  pool; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gen_pool_avail (int /*<<< orphan*/ ) ; 
 scalar_t__ gen_pool_size (int /*<<< orphan*/ ) ; 
 struct sram_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sram_free_partitions (struct sram_dev*) ; 

__attribute__((used)) static int sram_remove(struct platform_device *pdev)
{
	struct sram_dev *sram = platform_get_drvdata(pdev);

	sram_free_partitions(sram);

	if (gen_pool_avail(sram->pool) < gen_pool_size(sram->pool))
		dev_err(sram->dev, "removed while SRAM allocated\n");

	if (sram->clk)
		clk_disable_unprepare(sram->clk);

	return 0;
}