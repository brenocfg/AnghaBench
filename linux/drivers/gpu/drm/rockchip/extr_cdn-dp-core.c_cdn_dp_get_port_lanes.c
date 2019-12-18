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
union extcon_property_value {scalar_t__ intval; } ;
typedef  int u8 ;
struct extcon_dev {int dummy; } ;
struct cdn_dp_port {struct extcon_dev* extcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_DISP_DP ; 
 int /*<<< orphan*/  EXTCON_PROP_USB_SS ; 
 int /*<<< orphan*/  extcon_get_property (struct extcon_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union extcon_property_value*) ; 
 int extcon_get_state (struct extcon_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdn_dp_get_port_lanes(struct cdn_dp_port *port)
{
	struct extcon_dev *edev = port->extcon;
	union extcon_property_value property;
	int dptx;
	u8 lanes;

	dptx = extcon_get_state(edev, EXTCON_DISP_DP);
	if (dptx > 0) {
		extcon_get_property(edev, EXTCON_DISP_DP,
				    EXTCON_PROP_USB_SS, &property);
		if (property.intval)
			lanes = 2;
		else
			lanes = 4;
	} else {
		lanes = 0;
	}

	return lanes;
}