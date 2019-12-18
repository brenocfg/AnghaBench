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
struct usb_device {scalar_t__ serial; scalar_t__ product; scalar_t__ manufacturer; } ;

/* Variables and functions */
 char* format_string_manufacturer ; 
 char* format_string_product ; 
 char* format_string_serialnumber ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 

__attribute__((used)) static char *usb_dump_device_strings(char *start, char *end,
				     struct usb_device *dev)
{
	if (start > end)
		return start;
	if (dev->manufacturer)
		start += sprintf(start, format_string_manufacturer,
				 dev->manufacturer);
	if (start > end)
		goto out;
	if (dev->product)
		start += sprintf(start, format_string_product, dev->product);
	if (start > end)
		goto out;
#ifdef ALLOW_SERIAL_NUMBER
	if (dev->serial)
		start += sprintf(start, format_string_serialnumber,
				 dev->serial);
#endif
 out:
	return start;
}