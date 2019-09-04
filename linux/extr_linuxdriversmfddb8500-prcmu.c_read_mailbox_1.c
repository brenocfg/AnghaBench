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
struct TYPE_3__ {void* ape_voltage_status; void* ape_opp; void* arm_opp; void* header; } ;
struct TYPE_4__ {int /*<<< orphan*/  work; TYPE_1__ ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBOX_BIT (int) ; 
 scalar_t__ PRCM_ACK_MB1_APE_VOLTAGE_STATUS ; 
 scalar_t__ PRCM_ACK_MB1_CURRENT_APE_OPP ; 
 scalar_t__ PRCM_ACK_MB1_CURRENT_ARM_OPP ; 
 int /*<<< orphan*/  PRCM_ARM_IT1_CLR ; 
 scalar_t__ PRCM_MBOX_HEADER_REQ_MB1 ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_2__ mb1_transfer ; 
 void* readb (scalar_t__) ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool read_mailbox_1(void)
{
	mb1_transfer.ack.header = readb(tcdm_base + PRCM_MBOX_HEADER_REQ_MB1);
	mb1_transfer.ack.arm_opp = readb(tcdm_base +
		PRCM_ACK_MB1_CURRENT_ARM_OPP);
	mb1_transfer.ack.ape_opp = readb(tcdm_base +
		PRCM_ACK_MB1_CURRENT_APE_OPP);
	mb1_transfer.ack.ape_voltage_status = readb(tcdm_base +
		PRCM_ACK_MB1_APE_VOLTAGE_STATUS);
	writel(MBOX_BIT(1), PRCM_ARM_IT1_CLR);
	complete(&mb1_transfer.work);
	return false;
}