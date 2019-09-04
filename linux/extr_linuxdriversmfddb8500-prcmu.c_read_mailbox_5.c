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
struct TYPE_3__ {void* value; void* status; } ;
struct TYPE_4__ {int /*<<< orphan*/  work; TYPE_1__ ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBOX_BIT (int) ; 
 scalar_t__ PRCM_ACK_MB5_I2C_STATUS ; 
 scalar_t__ PRCM_ACK_MB5_I2C_VAL ; 
 int /*<<< orphan*/  PRCM_ARM_IT1_CLR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_2__ mb5_transfer ; 
 void* readb (scalar_t__) ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool read_mailbox_5(void)
{
	mb5_transfer.ack.status = readb(tcdm_base + PRCM_ACK_MB5_I2C_STATUS);
	mb5_transfer.ack.value = readb(tcdm_base + PRCM_ACK_MB5_I2C_VAL);
	writel(MBOX_BIT(5), PRCM_ARM_IT1_CLR);
	complete(&mb5_transfer.work);
	return false;
}