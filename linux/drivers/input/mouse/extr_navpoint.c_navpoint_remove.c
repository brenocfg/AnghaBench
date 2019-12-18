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
struct ssp_device {int /*<<< orphan*/  irq; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct navpoint_platform_data {int /*<<< orphan*/  gpio; } ;
struct navpoint {int /*<<< orphan*/  input; struct ssp_device* ssp; } ;

/* Variables and functions */
 struct navpoint_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct navpoint*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct navpoint*) ; 
 struct navpoint* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pxa_ssp_free (struct ssp_device*) ; 

__attribute__((used)) static int navpoint_remove(struct platform_device *pdev)
{
	const struct navpoint_platform_data *pdata =
					dev_get_platdata(&pdev->dev);
	struct navpoint *navpoint = platform_get_drvdata(pdev);
	struct ssp_device *ssp = navpoint->ssp;

	free_irq(ssp->irq, navpoint);

	input_unregister_device(navpoint->input);
	kfree(navpoint);

	pxa_ssp_free(ssp);

	if (gpio_is_valid(pdata->gpio))
		gpio_free(pdata->gpio);

	return 0;
}