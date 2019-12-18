#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  line; } ;
struct TYPE_4__ {TYPE_1__ port; } ;
struct bcm2835aux_data {int /*<<< orphan*/  clk; TYPE_2__ uart; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct bcm2835aux_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serial8250_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2835aux_serial_remove(struct platform_device *pdev)
{
	struct bcm2835aux_data *data = platform_get_drvdata(pdev);

	serial8250_unregister_port(data->uart.port.line);
	clk_disable_unprepare(data->clk);

	return 0;
}