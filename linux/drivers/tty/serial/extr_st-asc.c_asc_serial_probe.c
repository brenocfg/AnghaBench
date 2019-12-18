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
struct platform_device {int dummy; } ;
struct asc_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ENODEV ; 
 int asc_init_port (struct asc_port*,struct platform_device*) ; 
 struct asc_port* asc_of_get_asc_port (struct platform_device*) ; 
 int /*<<< orphan*/  asc_uart_driver ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asc_serial_probe(struct platform_device *pdev)
{
	int ret;
	struct asc_port *ascport;

	ascport = asc_of_get_asc_port(pdev);
	if (!ascport)
		return -ENODEV;

	ret = asc_init_port(ascport, pdev);
	if (ret)
		return ret;

	ret = uart_add_one_port(&asc_uart_driver, &ascport->port);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, &ascport->port);

	return 0;
}