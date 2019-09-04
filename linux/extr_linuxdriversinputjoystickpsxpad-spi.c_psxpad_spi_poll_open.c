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
struct psxpad {TYPE_1__* spi; } ;
struct input_polled_dev {struct psxpad* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psxpad_spi_poll_open(struct input_polled_dev *pdev)
{
	struct psxpad *pad = pdev->private;

	pm_runtime_get_sync(&pad->spi->dev);
}