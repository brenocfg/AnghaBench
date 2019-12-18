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
struct intf_priv {int dummy; } ;
struct intf_hdl {struct intf_priv* pintfpriv; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_usbctrl_vendorreq (struct intf_priv*,int,int,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static u8 usb_read8(struct intf_hdl *intfhdl, u32 addr)
{
	u8 request;
	u8 requesttype;
	u16 wvalue;
	u16 index;
	u16 len;
	__le32 data;
	struct intf_priv *intfpriv = intfhdl->pintfpriv;

	request = 0x05;
	requesttype = 0x01; /* read_in */
	index = 0;
	wvalue = (u16)(addr & 0x0000ffff);
	len = 1;
	r8712_usbctrl_vendorreq(intfpriv, request, wvalue, index, &data, len,
				requesttype);
	return (u8)(le32_to_cpu(data) & 0x0ff);
}