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
struct mps2_uart_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mps2_uart_port* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int mps2_init_port (struct platform_device*,struct mps2_uart_port*) ; 
 int mps2_of_get_port (struct platform_device*,struct mps2_uart_port*) ; 
 int /*<<< orphan*/  mps2_uart_driver ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mps2_uart_port*) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mps2_serial_probe(struct platform_device *pdev)
{
	struct mps2_uart_port *mps_port;
	int ret;

	mps_port = devm_kzalloc(&pdev->dev, sizeof(struct mps2_uart_port), GFP_KERNEL);

        if (!mps_port)
                return -ENOMEM;

	ret = mps2_of_get_port(pdev, mps_port);
	if (ret)
		return ret;

	ret = mps2_init_port(pdev, mps_port);
	if (ret)
		return ret;

	ret = uart_add_one_port(&mps2_uart_driver, &mps_port->port);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, mps_port);

	return 0;
}