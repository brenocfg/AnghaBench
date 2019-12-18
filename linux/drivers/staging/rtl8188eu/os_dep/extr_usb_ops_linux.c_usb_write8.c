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
typedef  int u32 ;
typedef  int u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int usbctrl_vendorreq (struct adapter*,int,int,int,int*,int,int) ; 

int usb_write8(struct adapter *adapter, u32 addr, u8 val)
{
	u8 request;
	u8 requesttype;
	u16 wvalue;
	u16 index;
	u16 len;
	u8 data;

	request = 0x05;
	requesttype = 0x00;/* write_out */
	index = 0;/* n/a */
	wvalue = (u16)(addr & 0x0000ffff);
	len = 1;
	data = val;
	return usbctrl_vendorreq(adapter, request, wvalue,
				 index, &data, len, requesttype);
}