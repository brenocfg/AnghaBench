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
struct usb_interface_assoc_descriptor {int /*<<< orphan*/  bFunctionProtocol; int /*<<< orphan*/  bFunctionSubClass; int /*<<< orphan*/  bFunctionClass; int /*<<< orphan*/  bInterfaceCount; int /*<<< orphan*/  bFirstInterface; } ;

/* Variables and functions */
 int /*<<< orphan*/  class_decode (int /*<<< orphan*/ ) ; 
 char* format_iad ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *usb_dump_iad_descriptor(char *start, char *end,
			const struct usb_interface_assoc_descriptor *iad)
{
	if (start > end)
		return start;
	start += sprintf(start, format_iad,
			 iad->bFirstInterface,
			 iad->bInterfaceCount,
			 iad->bFunctionClass,
			 class_decode(iad->bFunctionClass),
			 iad->bFunctionSubClass,
			 iad->bFunctionProtocol);
	return start;
}