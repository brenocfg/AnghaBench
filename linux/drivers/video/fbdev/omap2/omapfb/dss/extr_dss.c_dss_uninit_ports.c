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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
typedef  enum omap_display_type { ____Placeholder_omap_display_type } omap_display_type ;
struct TYPE_6__ {TYPE_2__* feat; } ;
struct TYPE_5__ {scalar_t__ num_ports; int* ports; } ;

/* Variables and functions */
#define  OMAP_DISPLAY_TYPE_DPI 129 
#define  OMAP_DISPLAY_TYPE_SDI 128 
 int /*<<< orphan*/  dpi_uninit_port (struct device_node*) ; 
 TYPE_3__ dss ; 
 int of_property_read_u32 (struct device_node*,char*,size_t*) ; 
 struct device_node* omapdss_of_get_next_port (struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  sdi_uninit_port (struct device_node*) ; 

__attribute__((used)) static void dss_uninit_ports(struct platform_device *pdev)
{
	struct device_node *parent = pdev->dev.of_node;
	struct device_node *port;

	if (parent == NULL)
		return;

	port = omapdss_of_get_next_port(parent, NULL);
	if (!port)
		return;

	if (dss.feat->num_ports == 0)
		return;

	do {
		enum omap_display_type port_type;
		u32 reg;
		int r;

		r = of_property_read_u32(port, "reg", &reg);
		if (r)
			reg = 0;

		if (reg >= dss.feat->num_ports)
			continue;

		port_type = dss.feat->ports[reg];

		switch (port_type) {
		case OMAP_DISPLAY_TYPE_DPI:
			dpi_uninit_port(port);
			break;
		case OMAP_DISPLAY_TYPE_SDI:
			sdi_uninit_port(port);
			break;
		default:
			break;
		}
	} while ((port = omapdss_of_get_next_port(parent, port)) != NULL);
}