#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {scalar_t__ fifosize; int /*<<< orphan*/  irq; } ;
struct uart_8250_port {scalar_t__ overrun_backoff_time_ms; TYPE_3__ port; int /*<<< orphan*/  capabilities; scalar_t__ tx_loadsz; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_serial_info {unsigned int type; int line; int /*<<< orphan*/  clk; } ;
typedef  int /*<<< orphan*/  port8250 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PORT_UNKNOWN ; 
 int /*<<< orphan*/  UART_CAP_AFE ; 
 int /*<<< orphan*/  UART_CAP_FIFO ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct of_serial_info*) ; 
 struct of_serial_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 
 int of_platform_serial_setup (struct platform_device*,unsigned int,TYPE_3__*,struct of_serial_info*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct of_serial_info*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (TYPE_1__*) ; 
 int serial8250_register_8250_port (struct uart_8250_port*) ; 

__attribute__((used)) static int of_platform_serial_probe(struct platform_device *ofdev)
{
	struct of_serial_info *info;
	struct uart_8250_port port8250;
	unsigned int port_type;
	u32 tx_threshold;
	int ret;

	port_type = (unsigned long)of_device_get_match_data(&ofdev->dev);
	if (port_type == PORT_UNKNOWN)
		return -EINVAL;

	if (of_property_read_bool(ofdev->dev.of_node, "used-by-rtas"))
		return -EBUSY;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (info == NULL)
		return -ENOMEM;

	memset(&port8250, 0, sizeof(port8250));
	ret = of_platform_serial_setup(ofdev, port_type, &port8250.port, info);
	if (ret)
		goto err_free;

	if (port8250.port.fifosize)
		port8250.capabilities = UART_CAP_FIFO;

	/* Check for TX FIFO threshold & set tx_loadsz */
	if ((of_property_read_u32(ofdev->dev.of_node, "tx-threshold",
				  &tx_threshold) == 0) &&
	    (tx_threshold < port8250.port.fifosize))
		port8250.tx_loadsz = port8250.port.fifosize - tx_threshold;

	if (of_property_read_bool(ofdev->dev.of_node, "auto-flow-control"))
		port8250.capabilities |= UART_CAP_AFE;

	if (of_property_read_u32(ofdev->dev.of_node,
			"overrun-throttle-ms",
			&port8250.overrun_backoff_time_ms) != 0)
		port8250.overrun_backoff_time_ms = 0;

	ret = serial8250_register_8250_port(&port8250);
	if (ret < 0)
		goto err_dispose;

	info->type = port_type;
	info->line = ret;
	platform_set_drvdata(ofdev, info);
	return 0;
err_dispose:
	irq_dispose_mapping(port8250.port.irq);
	pm_runtime_put_sync(&ofdev->dev);
	pm_runtime_disable(&ofdev->dev);
	clk_disable_unprepare(info->clk);
err_free:
	kfree(info);
	return ret;
}