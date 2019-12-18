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
struct gb_interface {int dummy; } ;
typedef  enum gb_interface_type { ____Placeholder_gb_interface_type } gb_interface_type ;

/* Variables and functions */
 int ENODEV ; 
 int GB_INTERFACE_TYPE_UNIPRO ; 
 int _gb_interface_activate (struct gb_interface*,int*) ; 

__attribute__((used)) static int _gb_interface_activate_es3_hack(struct gb_interface *intf,
					   enum gb_interface_type *type)
{
	int retries = 3;
	int ret;

	while (retries--) {
		ret = _gb_interface_activate(intf, type);
		if (ret == -ENODEV && *type == GB_INTERFACE_TYPE_UNIPRO)
			continue;

		break;
	}

	return ret;
}