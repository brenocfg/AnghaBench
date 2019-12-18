#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int XferState; scalar_t__ Command; } ;
struct hw_fib {TYPE_3__ header; scalar_t__ data; } ;
struct fib {int flags; int done; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  event_wait; int /*<<< orphan*/  callback_data; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,struct fib*) ;struct hw_fib* hw_fib_va; } ;
struct aac_queue {int /*<<< orphan*/ * lock; struct aac_dev* dev; } ;
struct aac_entry {int /*<<< orphan*/  addr; } ;
struct aac_dev {int /*<<< orphan*/  manage_lock; int /*<<< orphan*/  management_fib_count; TYPE_2__* queues; struct fib* fibs; } ;
typedef  int __le32 ;
struct TYPE_8__ {int peak_fibs; int /*<<< orphan*/  zero_fibs; int /*<<< orphan*/  NormalRecved; int /*<<< orphan*/  AsyncRecved; int /*<<< orphan*/  NoResponseRecved; int /*<<< orphan*/  FibRecved; } ;
struct TYPE_6__ {TYPE_1__* queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  numpending; } ;

/* Variables and functions */
 size_t AdapNormCmdQueue ; 
 int AdapterProcessed ; 
 int Async ; 
 int FIB_CONTEXT_FLAG_FASTRESP ; 
 int FIB_CONTEXT_FLAG_TIMED_OUT ; 
 int /*<<< orphan*/  FIB_COUNTER_INCREMENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HostNormRespQueue ; 
 int NoResponseExpected ; 
 int /*<<< orphan*/  NuFileSystem ; 
 int ST_OK ; 
 TYPE_4__ aac_config ; 
 int /*<<< orphan*/  aac_consumer_free (struct aac_dev*,struct aac_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ aac_consumer_get (struct aac_dev*,struct aac_queue*,struct aac_entry**) ; 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_free (struct fib*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct fib*) ; 
 scalar_t__ unlikely (int) ; 

unsigned int aac_response_normal(struct aac_queue * q)
{
	struct aac_dev * dev = q->dev;
	struct aac_entry *entry;
	struct hw_fib * hwfib;
	struct fib * fib;
	int consumed = 0;
	unsigned long flags, mflags;

	spin_lock_irqsave(q->lock, flags);
	/*
	 *	Keep pulling response QEs off the response queue and waking
	 *	up the waiters until there are no more QEs. We then return
	 *	back to the system. If no response was requested we just
	 *	deallocate the Fib here and continue.
	 */
	while(aac_consumer_get(dev, q, &entry))
	{
		int fast;
		u32 index = le32_to_cpu(entry->addr);
		fast = index & 0x01;
		fib = &dev->fibs[index >> 2];
		hwfib = fib->hw_fib_va;
		
		aac_consumer_free(dev, q, HostNormRespQueue);
		/*
		 *	Remove this fib from the Outstanding I/O queue.
		 *	But only if it has not already been timed out.
		 *
		 *	If the fib has been timed out already, then just 
		 *	continue. The caller has already been notified that
		 *	the fib timed out.
		 */
		atomic_dec(&dev->queues->queue[AdapNormCmdQueue].numpending);

		if (unlikely(fib->flags & FIB_CONTEXT_FLAG_TIMED_OUT)) {
			spin_unlock_irqrestore(q->lock, flags);
			aac_fib_complete(fib);
			aac_fib_free(fib);
			spin_lock_irqsave(q->lock, flags);
			continue;
		}
		spin_unlock_irqrestore(q->lock, flags);

		if (fast) {
			/*
			 *	Doctor the fib
			 */
			*(__le32 *)hwfib->data = cpu_to_le32(ST_OK);
			hwfib->header.XferState |= cpu_to_le32(AdapterProcessed);
			fib->flags |= FIB_CONTEXT_FLAG_FASTRESP;
		}

		FIB_COUNTER_INCREMENT(aac_config.FibRecved);

		if (hwfib->header.Command == cpu_to_le16(NuFileSystem))
		{
			__le32 *pstatus = (__le32 *)hwfib->data;
			if (*pstatus & cpu_to_le32(0xffff0000))
				*pstatus = cpu_to_le32(ST_OK);
		}
		if (hwfib->header.XferState & cpu_to_le32(NoResponseExpected | Async)) 
		{
	        	if (hwfib->header.XferState & cpu_to_le32(NoResponseExpected))
				FIB_COUNTER_INCREMENT(aac_config.NoResponseRecved);
			else 
				FIB_COUNTER_INCREMENT(aac_config.AsyncRecved);
			/*
			 *	NOTE:  we cannot touch the fib after this
			 *	    call, because it may have been deallocated.
			 */
			fib->callback(fib->callback_data, fib);
		} else {
			unsigned long flagv;
			spin_lock_irqsave(&fib->event_lock, flagv);
			if (!fib->done) {
				fib->done = 1;
				complete(&fib->event_wait);
			}
			spin_unlock_irqrestore(&fib->event_lock, flagv);

			spin_lock_irqsave(&dev->manage_lock, mflags);
			dev->management_fib_count--;
			spin_unlock_irqrestore(&dev->manage_lock, mflags);

			FIB_COUNTER_INCREMENT(aac_config.NormalRecved);
			if (fib->done == 2) {
				spin_lock_irqsave(&fib->event_lock, flagv);
				fib->done = 0;
				spin_unlock_irqrestore(&fib->event_lock, flagv);
				aac_fib_complete(fib);
				aac_fib_free(fib);
			}
		}
		consumed++;
		spin_lock_irqsave(q->lock, flags);
	}

	if (consumed > aac_config.peak_fibs)
		aac_config.peak_fibs = consumed;
	if (consumed == 0) 
		aac_config.zero_fibs++;

	spin_unlock_irqrestore(q->lock, flags);
	return 0;
}