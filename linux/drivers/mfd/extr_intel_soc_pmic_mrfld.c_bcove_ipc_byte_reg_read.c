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
typedef  unsigned int u8 ;

/* Variables and functions */
 int intel_scu_ipc_ioread8 (unsigned int,unsigned int*) ; 

__attribute__((used)) static int bcove_ipc_byte_reg_read(void *context, unsigned int reg,
				    unsigned int *val)
{
	u8 ipc_out;
	int ret;

	ret = intel_scu_ipc_ioread8(reg, &ipc_out);
	if (ret)
		return ret;

	*val = ipc_out;
	return 0;
}