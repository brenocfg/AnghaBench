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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 unsigned int CIM_VF_EXT_MAILBOX_CTRL ; 
 unsigned int T4VF_CIM_BASE_ADDR ; 
 void* T4VF_REGMAP_START ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,unsigned int) ; 

__attribute__((used)) static void reg_block_dump(struct adapter *adapter, void *regbuf,
			   unsigned int start, unsigned int end)
{
	u32 *bp = regbuf + start - T4VF_REGMAP_START;

	for ( ; start <= end; start += sizeof(u32)) {
		/*
		 * Avoid reading the Mailbox Control register since that
		 * can trigger a Mailbox Ownership Arbitration cycle and
		 * interfere with communication with the firmware.
		 */
		if (start == T4VF_CIM_BASE_ADDR + CIM_VF_EXT_MAILBOX_CTRL)
			*bp++ = 0xffff;
		else
			*bp++ = t4_read_reg(adapter, start);
	}
}