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
typedef  scalar_t__ u8 ;
struct nic {int /*<<< orphan*/  cmd_lock; TYPE_2__* csr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  cmd_lo; int /*<<< orphan*/  gen_ptr; } ;
struct TYPE_4__ {TYPE_1__ scb; } ;

/* Variables and functions */
 unsigned int E100_WAIT_SCB_FAST ; 
 unsigned int E100_WAIT_SCB_TIMEOUT ; 
 int EAGAIN ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ cuc_resume ; 
 int /*<<< orphan*/  ioread8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int e100_exec_cmd(struct nic *nic, u8 cmd, dma_addr_t dma_addr)
{
	unsigned long flags;
	unsigned int i;
	int err = 0;

	spin_lock_irqsave(&nic->cmd_lock, flags);

	/* Previous command is accepted when SCB clears */
	for (i = 0; i < E100_WAIT_SCB_TIMEOUT; i++) {
		if (likely(!ioread8(&nic->csr->scb.cmd_lo)))
			break;
		cpu_relax();
		if (unlikely(i > E100_WAIT_SCB_FAST))
			udelay(5);
	}
	if (unlikely(i == E100_WAIT_SCB_TIMEOUT)) {
		err = -EAGAIN;
		goto err_unlock;
	}

	if (unlikely(cmd != cuc_resume))
		iowrite32(dma_addr, &nic->csr->scb.gen_ptr);
	iowrite8(cmd, &nic->csr->scb.cmd_lo);

err_unlock:
	spin_unlock_irqrestore(&nic->cmd_lock, flags);

	return err;
}