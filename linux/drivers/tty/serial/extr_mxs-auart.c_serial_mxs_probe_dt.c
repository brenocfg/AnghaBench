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
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_3__ {int line; } ;
struct mxs_auart_port {int /*<<< orphan*/  flags; TYPE_1__ port; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXS_AUART_RTSCTS ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int serial_mxs_probe_dt(struct mxs_auart_port *s,
		struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	int ret;

	if (!np)
		/* no device tree device */
		return 1;

	ret = of_alias_get_id(np, "serial");
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to get alias id: %d\n", ret);
		return ret;
	}
	s->port.line = ret;

	if (of_get_property(np, "uart-has-rtscts", NULL) ||
	    of_get_property(np, "fsl,uart-has-rtscts", NULL) /* deprecated */)
		set_bit(MXS_AUART_RTSCTS, &s->flags);

	return 0;
}