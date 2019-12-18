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
struct spi_sh_data {int /*<<< orphan*/  irq; int /*<<< orphan*/  ws; int /*<<< orphan*/  master; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct spi_sh_data*) ; 
 struct spi_sh_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spi_unregister_master (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_sh_remove(struct platform_device *pdev)
{
	struct spi_sh_data *ss = platform_get_drvdata(pdev);

	spi_unregister_master(ss->master);
	flush_work(&ss->ws);
	free_irq(ss->irq, ss);

	return 0;
}