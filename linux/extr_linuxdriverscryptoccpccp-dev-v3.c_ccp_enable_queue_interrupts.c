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
struct ccp_device {scalar_t__ io_regs; int /*<<< orphan*/  qim; } ;

/* Variables and functions */
 scalar_t__ IRQ_MASK_REG ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ccp_enable_queue_interrupts(struct ccp_device *ccp)
{
	iowrite32(ccp->qim, ccp->io_regs + IRQ_MASK_REG);
}