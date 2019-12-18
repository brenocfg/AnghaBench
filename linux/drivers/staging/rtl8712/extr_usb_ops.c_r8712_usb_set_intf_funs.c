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
struct intf_hdl {int /*<<< orphan*/  intf_hdl_close; int /*<<< orphan*/  intf_hdl_open; int /*<<< orphan*/  intf_hdl_unload; int /*<<< orphan*/  intf_hdl_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_intf_hdl_close ; 
 int /*<<< orphan*/  usb_intf_hdl_init ; 
 int /*<<< orphan*/  usb_intf_hdl_open ; 
 int /*<<< orphan*/  usb_intf_hdl_unload ; 

void r8712_usb_set_intf_funs(struct intf_hdl *intfhdl)
{
	intfhdl->intf_hdl_init = usb_intf_hdl_init;
	intfhdl->intf_hdl_unload = usb_intf_hdl_unload;
	intfhdl->intf_hdl_open = usb_intf_hdl_open;
	intfhdl->intf_hdl_close = usb_intf_hdl_close;
}