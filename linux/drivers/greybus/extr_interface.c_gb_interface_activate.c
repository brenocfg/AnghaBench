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
struct gb_interface {int type; int /*<<< orphan*/  dev; } ;
typedef  enum gb_interface_type { ____Placeholder_gb_interface_type } gb_interface_type ;

/* Variables and functions */
 int EIO ; 
#define  GB_INTERFACE_TYPE_GREYBUS 129 
#define  GB_INTERFACE_TYPE_INVALID 128 
 int _gb_interface_activate (struct gb_interface*,int*) ; 
 int _gb_interface_activate_es3_hack (struct gb_interface*,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gb_interface_deactivate (struct gb_interface*) ; 

int gb_interface_activate(struct gb_interface *intf)
{
	enum gb_interface_type type;
	int ret;

	switch (intf->type) {
	case GB_INTERFACE_TYPE_INVALID:
	case GB_INTERFACE_TYPE_GREYBUS:
		ret = _gb_interface_activate_es3_hack(intf, &type);
		break;
	default:
		ret = _gb_interface_activate(intf, &type);
	}

	/* Make sure type is detected correctly during reactivation. */
	if (intf->type != GB_INTERFACE_TYPE_INVALID) {
		if (type != intf->type) {
			dev_err(&intf->dev, "failed to detect interface type\n");

			if (!ret)
				gb_interface_deactivate(intf);

			return -EIO;
		}
	} else {
		intf->type = type;
	}

	return ret;
}