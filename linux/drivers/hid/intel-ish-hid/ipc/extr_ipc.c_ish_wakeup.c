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
struct ishtp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_DRBL_BUSY_BIT ; 
 int /*<<< orphan*/  IPC_REG_HOST2ISH_DRBL ; 
 int /*<<< orphan*/  IPC_REG_ISH_HOST_FWSTS ; 
 int /*<<< orphan*/  IPC_REG_ISH_RMP2 ; 
 int /*<<< orphan*/  IPC_RMP2_DMA_ENABLED ; 
 int /*<<< orphan*/  ish_reg_read (struct ishtp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ish_reg_write (struct ishtp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ish_wakeup(struct ishtp_device *dev)
{
	/* Set dma enable bit */
	ish_reg_write(dev, IPC_REG_ISH_RMP2, IPC_RMP2_DMA_ENABLED);

	/*
	 * Send 0 IPC message so that ISH FW wakes up if it was already
	 * asleep.
	 */
	ish_reg_write(dev, IPC_REG_HOST2ISH_DRBL, IPC_DRBL_BUSY_BIT);

	/* Flush writes to doorbell and REMAP2 */
	ish_reg_read(dev, IPC_REG_ISH_HOST_FWSTS);
}