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
struct intf_hdl {int /*<<< orphan*/  pintfpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _unload_intf_hdl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static  void unregister_intf_hdl(struct intf_hdl *pintfhdl)
{
	_unload_intf_hdl(pintfhdl->pintfpriv);
	memset((u8 *)pintfhdl, 0, sizeof(struct intf_hdl));
}