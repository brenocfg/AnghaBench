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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  USB_EXT_PROP_W_PROPERTY_NAME_LENGTH ; 
 int /*<<< orphan*/ * __usb_ext_prop_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 *usb_ext_prop_name_len_ptr(u8 *buf)
{
	return __usb_ext_prop_ptr(buf, USB_EXT_PROP_W_PROPERTY_NAME_LENGTH);
}