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
struct tegra_output {TYPE_1__* ddc; int /*<<< orphan*/  hpd_irq; scalar_t__ hpd_gpio; scalar_t__ cec; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_notifier_put (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct tegra_output*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void tegra_output_remove(struct tegra_output *output)
{
	if (output->cec)
		cec_notifier_put(output->cec);

	if (output->hpd_gpio)
		free_irq(output->hpd_irq, output);

	if (output->ddc)
		put_device(&output->ddc->dev);
}