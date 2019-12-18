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
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
struct intf_hdl {int /*<<< orphan*/ * intf_dev; int /*<<< orphan*/ * adapter; scalar_t__ intf_option; } ;
struct _adapter {int /*<<< orphan*/  dvobjpriv; } ;

/* Variables and functions */
 int _SUCCESS ; 
 int /*<<< orphan*/  _init_intf_hdl (struct _adapter*,struct intf_hdl*) ; 

__attribute__((used)) static uint register_intf_hdl(u8 *dev, struct intf_hdl *pintfhdl)
{
	struct _adapter *adapter = (struct _adapter *)dev;

	pintfhdl->intf_option = 0;
	pintfhdl->adapter = dev;
	pintfhdl->intf_dev = (u8 *)&adapter->dvobjpriv;
	if (!_init_intf_hdl(adapter, pintfhdl))
		goto register_intf_hdl_fail;
	return _SUCCESS;
register_intf_hdl_fail:
	return false;
}