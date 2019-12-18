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
typedef  int u8 ;

/* Variables and functions */
#define  GREYBUS_TYPE_BUNDLE 132 
#define  GREYBUS_TYPE_CPORT 131 
#define  GREYBUS_TYPE_INTERFACE 130 
#define  GREYBUS_TYPE_INVALID 129 
#define  GREYBUS_TYPE_STRING 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static const char *get_descriptor_type_string(u8 type)
{
	switch (type) {
	case GREYBUS_TYPE_INVALID:
		return "invalid";
	case GREYBUS_TYPE_STRING:
		return "string";
	case GREYBUS_TYPE_INTERFACE:
		return "interface";
	case GREYBUS_TYPE_CPORT:
		return "cport";
	case GREYBUS_TYPE_BUNDLE:
		return "bundle";
	default:
		WARN_ON(1);
		return "unknown";
	}
}