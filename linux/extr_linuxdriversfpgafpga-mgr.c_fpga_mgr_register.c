#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct fpga_manager {TYPE_2__ dev; int /*<<< orphan*/  name; TYPE_1__* mops; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* state ) (struct fpga_manager*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  fpga_mgr_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fpga_manager*) ; 

int fpga_mgr_register(struct fpga_manager *mgr)
{
	int ret;

	/*
	 * Initialize framework state by requesting low level driver read state
	 * from device.  FPGA may be in reset mode or may have been programmed
	 * by bootloader or EEPROM.
	 */
	mgr->state = mgr->mops->state(mgr);

	ret = device_add(&mgr->dev);
	if (ret)
		goto error_device;

	dev_info(&mgr->dev, "%s registered\n", mgr->name);

	return 0;

error_device:
	ida_simple_remove(&fpga_mgr_ida, mgr->dev.id);

	return ret;
}