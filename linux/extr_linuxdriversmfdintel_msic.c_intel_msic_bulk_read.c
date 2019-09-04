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

/* Variables and functions */
 int EINVAL ; 
 size_t SCU_IPC_RWBUF_LIMIT ; 
 scalar_t__ WARN_ON (int) ; 
 int intel_scu_ipc_readv (unsigned short*,int /*<<< orphan*/ *,size_t) ; 

int intel_msic_bulk_read(unsigned short *reg, u8 *buf, size_t count)
{
	if (WARN_ON(count > SCU_IPC_RWBUF_LIMIT))
		return -EINVAL;

	return intel_scu_ipc_readv(reg, buf, count);
}