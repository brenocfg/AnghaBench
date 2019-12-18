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
struct platform_device {TYPE_2__* id_entry; int /*<<< orphan*/  id; int /*<<< orphan*/  dev; } ;
struct imxuart_platform_data {int flags; } ;
struct imx_uart_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  line; } ;
struct imx_port {int have_rtscts; struct imx_uart_data* devdata; TYPE_1__ port; } ;
struct TYPE_4__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int IMXUART_HAVE_RTSCTS ; 
 struct imxuart_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void imx_uart_probe_pdata(struct imx_port *sport,
				 struct platform_device *pdev)
{
	struct imxuart_platform_data *pdata = dev_get_platdata(&pdev->dev);

	sport->port.line = pdev->id;
	sport->devdata = (struct imx_uart_data	*) pdev->id_entry->driver_data;

	if (!pdata)
		return;

	if (pdata->flags & IMXUART_HAVE_RTSCTS)
		sport->have_rtscts = 1;
}