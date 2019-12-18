#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_12__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  quiescent; TYPE_2__* mbox; int /*<<< orphan*/  pend_cmds; } ;
typedef  TYPE_3__ adapter_t ;
struct TYPE_10__ {int numstatus; int status; scalar_t__ completed; } ;
struct TYPE_11__ {TYPE_1__ m_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int MAX_FIRMWARE_STATUS ; 
 int VALID_INTR_BYTE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  irq_ack (TYPE_3__*) ; 
 int irq_state (TYPE_3__*) ; 
 int /*<<< orphan*/  mega_cmd_done (TYPE_3__*,int*,int,int) ; 
 int /*<<< orphan*/  mega_rundoneq (TYPE_3__*) ; 
 int /*<<< orphan*/  mega_runpendq (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int*,void*,int) ; 
 int /*<<< orphan*/  set_irq_state (TYPE_3__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t
megaraid_isr_iomapped(int irq, void *devp)
{
	adapter_t	*adapter = devp;
	unsigned long	flags;
	u8	status;
	u8	nstatus;
	u8	completed[MAX_FIRMWARE_STATUS];
	u8	byte;
	int	handled = 0;


	/*
	 * loop till F/W has more commands for us to complete.
	 */
	spin_lock_irqsave(&adapter->lock, flags);

	do {
		/* Check if a valid interrupt is pending */
		byte = irq_state(adapter);
		if( (byte & VALID_INTR_BYTE) == 0 ) {
			/*
			 * No more pending commands
			 */
			goto out_unlock;
		}
		set_irq_state(adapter, byte);

		while((nstatus = (volatile u8)adapter->mbox->m_in.numstatus)
				== 0xFF)
			cpu_relax();
		adapter->mbox->m_in.numstatus = 0xFF;

		status = adapter->mbox->m_in.status;

		/*
		 * decrement the pending queue counter
		 */
		atomic_sub(nstatus, &adapter->pend_cmds);

		memcpy(completed, (void *)adapter->mbox->m_in.completed, 
				nstatus);

		/* Acknowledge interrupt */
		irq_ack(adapter);

		mega_cmd_done(adapter, completed, nstatus, status);

		mega_rundoneq(adapter);

		handled = 1;

		/* Loop through any pending requests */
		if(atomic_read(&adapter->quiescent) == 0) {
			mega_runpendq(adapter);
		}

	} while(1);

 out_unlock:

	spin_unlock_irqrestore(&adapter->lock, flags);

	return IRQ_RETVAL(handled);
}