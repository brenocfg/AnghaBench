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
struct gb_interface {size_t type; } ;

/* Variables and functions */
#define  GB_INTERFACE_TYPE_DUMMY 132 
#define  GB_INTERFACE_TYPE_GREYBUS 131 
#define  GB_INTERFACE_TYPE_INVALID 130 
#define  GB_INTERFACE_TYPE_UNIPRO 129 
#define  GB_INTERFACE_TYPE_UNKNOWN 128 

__attribute__((used)) static const char *gb_interface_type_string(struct gb_interface *intf)
{
	static const char * const types[] = {
		[GB_INTERFACE_TYPE_INVALID] = "invalid",
		[GB_INTERFACE_TYPE_UNKNOWN] = "unknown",
		[GB_INTERFACE_TYPE_DUMMY] = "dummy",
		[GB_INTERFACE_TYPE_UNIPRO] = "unipro",
		[GB_INTERFACE_TYPE_GREYBUS] = "greybus",
	};

	return types[intf->type];
}