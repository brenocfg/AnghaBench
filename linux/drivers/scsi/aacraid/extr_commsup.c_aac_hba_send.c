#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct fib {int flags; int done; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  event_wait; void* callback_data; scalar_t__ callback; scalar_t__ hw_fib_va; struct aac_dev* dev; } ;
struct aac_hba_cmd_req {int /*<<< orphan*/  request_id; scalar_t__ iu_type; } ;
struct aac_dev {scalar_t__ management_fib_count; int /*<<< orphan*/  manage_lock; struct fib* fibs; } ;
typedef  scalar_t__ fib_callback ;
struct TYPE_2__ {int /*<<< orphan*/  NativeSent; } ;

/* Variables and functions */
 scalar_t__ AAC_NUM_MGT_FIB ; 
 int EBUSY ; 
 int EFAULT ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int ETIMEDOUT ; 
 int FIB_CONTEXT_FLAG ; 
 int FIB_CONTEXT_FLAG_NATIVE_HBA ; 
 int FIB_CONTEXT_FLAG_SCSI_CMD ; 
 int FIB_CONTEXT_FLAG_TIMED_OUT ; 
 int FIB_CONTEXT_FLAG_WAIT ; 
 int /*<<< orphan*/  FIB_COUNTER_INCREMENT (int /*<<< orphan*/ ) ; 
 scalar_t__ HBA_IU_TYPE_SCSI_CMD_REQ ; 
 scalar_t__ HBA_IU_TYPE_SCSI_TM_REQ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ aac_adapter_deliver (struct fib*) ; 
 TYPE_1__ aac_config ; 
 int aac_pci_offline (struct aac_dev*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

int aac_hba_send(u8 command, struct fib *fibptr, fib_callback callback,
		void *callback_data)
{
	struct aac_dev *dev = fibptr->dev;
	int wait;
	unsigned long flags = 0;
	unsigned long mflags = 0;
	struct aac_hba_cmd_req *hbacmd = (struct aac_hba_cmd_req *)
			fibptr->hw_fib_va;

	fibptr->flags = (FIB_CONTEXT_FLAG | FIB_CONTEXT_FLAG_NATIVE_HBA);
	if (callback) {
		wait = 0;
		fibptr->callback = callback;
		fibptr->callback_data = callback_data;
	} else
		wait = 1;


	hbacmd->iu_type = command;

	if (command == HBA_IU_TYPE_SCSI_CMD_REQ) {
		/* bit1 of request_id must be 0 */
		hbacmd->request_id =
			cpu_to_le32((((u32)(fibptr - dev->fibs)) << 2) + 1);
		fibptr->flags |= FIB_CONTEXT_FLAG_SCSI_CMD;
	} else if (command != HBA_IU_TYPE_SCSI_TM_REQ)
		return -EINVAL;


	if (wait) {
		spin_lock_irqsave(&dev->manage_lock, mflags);
		if (dev->management_fib_count >= AAC_NUM_MGT_FIB) {
			spin_unlock_irqrestore(&dev->manage_lock, mflags);
			return -EBUSY;
		}
		dev->management_fib_count++;
		spin_unlock_irqrestore(&dev->manage_lock, mflags);
		spin_lock_irqsave(&fibptr->event_lock, flags);
	}

	if (aac_adapter_deliver(fibptr) != 0) {
		if (wait) {
			spin_unlock_irqrestore(&fibptr->event_lock, flags);
			spin_lock_irqsave(&dev->manage_lock, mflags);
			dev->management_fib_count--;
			spin_unlock_irqrestore(&dev->manage_lock, mflags);
		}
		return -EBUSY;
	}
	FIB_COUNTER_INCREMENT(aac_config.NativeSent);

	if (wait) {

		spin_unlock_irqrestore(&fibptr->event_lock, flags);

		if (unlikely(aac_pci_offline(dev)))
			return -EFAULT;

		fibptr->flags |= FIB_CONTEXT_FLAG_WAIT;
		if (wait_for_completion_interruptible(&fibptr->event_wait))
			fibptr->done = 2;
		fibptr->flags &= ~(FIB_CONTEXT_FLAG_WAIT);

		spin_lock_irqsave(&fibptr->event_lock, flags);
		if ((fibptr->done == 0) || (fibptr->done == 2)) {
			fibptr->done = 2; /* Tell interrupt we aborted */
			spin_unlock_irqrestore(&fibptr->event_lock, flags);
			return -ERESTARTSYS;
		}
		spin_unlock_irqrestore(&fibptr->event_lock, flags);
		WARN_ON(fibptr->done == 0);

		if (unlikely(fibptr->flags & FIB_CONTEXT_FLAG_TIMED_OUT))
			return -ETIMEDOUT;

		return 0;
	}

	return -EINPROGRESS;
}