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

/* Variables and functions */
 scalar_t__ BUF ; 
 scalar_t__ SMP_CORE0_OFFSET ; 
 scalar_t__ SMP_CORE1_OFFSET ; 
 scalar_t__ SMP_CORE2_OFFSET ; 
 scalar_t__ SMP_CORE3_OFFSET ; 
 scalar_t__ SMP_CORE_GROUP0_BASE ; 
 scalar_t__ SMP_CORE_GROUP1_BASE ; 
 scalar_t__ SMP_CORE_GROUP2_BASE ; 
 scalar_t__ SMP_CORE_GROUP3_BASE ; 
 void** ipi_mailbox_buf ; 

__attribute__((used)) static void ipi_mailbox_buf_init(void)
{
	ipi_mailbox_buf[0] = (void *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE0_OFFSET + BUF);
	ipi_mailbox_buf[1] = (void *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE1_OFFSET + BUF);
	ipi_mailbox_buf[2] = (void *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE2_OFFSET + BUF);
	ipi_mailbox_buf[3] = (void *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE3_OFFSET + BUF);
	ipi_mailbox_buf[4] = (void *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE0_OFFSET + BUF);
	ipi_mailbox_buf[5] = (void *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE1_OFFSET + BUF);
	ipi_mailbox_buf[6] = (void *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE2_OFFSET + BUF);
	ipi_mailbox_buf[7] = (void *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE3_OFFSET + BUF);
	ipi_mailbox_buf[8] = (void *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE0_OFFSET + BUF);
	ipi_mailbox_buf[9] = (void *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE1_OFFSET + BUF);
	ipi_mailbox_buf[10] = (void *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE2_OFFSET + BUF);
	ipi_mailbox_buf[11] = (void *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE3_OFFSET + BUF);
	ipi_mailbox_buf[12] = (void *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE0_OFFSET + BUF);
	ipi_mailbox_buf[13] = (void *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE1_OFFSET + BUF);
	ipi_mailbox_buf[14] = (void *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE2_OFFSET + BUF);
	ipi_mailbox_buf[15] = (void *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE3_OFFSET + BUF);
}