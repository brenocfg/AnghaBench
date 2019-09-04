#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  device_name; scalar_t__ irq_level; int /*<<< orphan*/  init_error; scalar_t__ io_base; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int /*<<< orphan*/  DiagStatus_AddressFailure ; 
 int /*<<< orphan*/  DiagStatus_IrqFailure ; 
 int ENODEV ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  irq_test (TYPE_1__*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  register_test (TYPE_1__*) ; 

__attribute__((used)) static int adapter_test(MGSLPC_INFO *info)
{
	if (!register_test(info)) {
		info->init_error = DiagStatus_AddressFailure;
		printk("%s(%d):Register test failure for device %s Addr=%04X\n",
			__FILE__, __LINE__, info->device_name, (unsigned short)(info->io_base));
		return -ENODEV;
	}

	if (!irq_test(info)) {
		info->init_error = DiagStatus_IrqFailure;
		printk("%s(%d):Interrupt test failure for device %s IRQ=%d\n",
			__FILE__, __LINE__, info->device_name, (unsigned short)(info->irq_level));
		return -ENODEV;
	}

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):device %s passed diagnostics\n",
			__FILE__, __LINE__, info->device_name);
	return 0;
}