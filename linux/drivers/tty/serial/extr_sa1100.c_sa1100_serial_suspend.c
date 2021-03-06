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
struct sa1100_port {int /*<<< orphan*/  port; } ;
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 struct sa1100_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sa1100_reg ; 
 int /*<<< orphan*/  uart_suspend_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sa1100_serial_suspend(struct platform_device *dev, pm_message_t state)
{
	struct sa1100_port *sport = platform_get_drvdata(dev);

	if (sport)
		uart_suspend_port(&sa1100_reg, &sport->port);

	return 0;
}