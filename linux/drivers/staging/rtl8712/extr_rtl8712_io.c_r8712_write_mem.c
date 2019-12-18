#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  (* _write_mem ) (struct intf_hdl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct intf_hdl {TYPE_2__ io_ops; } ;
struct _adapter {TYPE_1__* pio_queue; } ;
struct TYPE_3__ {struct intf_hdl intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct intf_hdl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void r8712_write_mem(struct _adapter *adapter, u32 addr, u32 cnt, u8 *pmem)
{
	struct intf_hdl *hdl = &adapter->pio_queue->intf;

	hdl->io_ops._write_mem(hdl, addr, cnt, pmem);
}