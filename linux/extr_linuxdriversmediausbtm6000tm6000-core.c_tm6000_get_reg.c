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
typedef  int /*<<< orphan*/  u16 ;
struct tm6000_core {int dummy; } ;

/* Variables and functions */
 int USB_DIR_IN ; 
 int USB_TYPE_VENDOR ; 
 int tm6000_read_write_usb (struct tm6000_core*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int tm6000_get_reg(struct tm6000_core *dev, u8 req, u16 value, u16 index)
{
	int rc;
	u8 buf[1];

	rc = tm6000_read_write_usb(dev, USB_DIR_IN | USB_TYPE_VENDOR, req,
					value, index, buf, 1);

	if (rc < 0)
		return rc;

	return *buf;
}