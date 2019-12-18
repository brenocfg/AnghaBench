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
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct dss_device {TYPE_2__* feat; struct platform_device* pdev; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {unsigned int num_ports; int* ports; int /*<<< orphan*/  model; } ;

/* Variables and functions */
#define  OMAP_DISPLAY_TYPE_DPI 129 
#define  OMAP_DISPLAY_TYPE_SDI 128 
 int dpi_init_port (struct dss_device*,struct platform_device*,struct device_node*,int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_port_by_id (struct device_node*,unsigned int) ; 
 int sdi_init_port (struct dss_device*,struct platform_device*,struct device_node*) ; 

__attribute__((used)) static int dss_init_ports(struct dss_device *dss)
{
	struct platform_device *pdev = dss->pdev;
	struct device_node *parent = pdev->dev.of_node;
	struct device_node *port;
	unsigned int i;
	int r;

	for (i = 0; i < dss->feat->num_ports; i++) {
		port = of_graph_get_port_by_id(parent, i);
		if (!port)
			continue;

		switch (dss->feat->ports[i]) {
		case OMAP_DISPLAY_TYPE_DPI:
			r = dpi_init_port(dss, pdev, port, dss->feat->model);
			if (r)
				return r;
			break;

		case OMAP_DISPLAY_TYPE_SDI:
			r = sdi_init_port(dss, pdev, port);
			if (r)
				return r;
			break;

		default:
			break;
		}
	}

	return 0;
}