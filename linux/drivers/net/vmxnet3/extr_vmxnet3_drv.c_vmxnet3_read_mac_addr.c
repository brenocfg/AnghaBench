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
struct vmxnet3_adapter {int dummy; } ;

/* Variables and functions */
 int VMXNET3_READ_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMXNET3_REG_MACH ; 
 int /*<<< orphan*/  VMXNET3_REG_MACL ; 

__attribute__((used)) static void
vmxnet3_read_mac_addr(struct vmxnet3_adapter *adapter, u8 *mac)
{
	u32 tmp;

	tmp = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_MACL);
	*(u32 *)mac = tmp;

	tmp = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_MACH);
	mac[4] = tmp & 0xff;
	mac[5] = (tmp >> 8) & 0xff;
}