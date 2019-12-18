#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wait; } ;
struct TYPE_6__ {TYPE_2__ wq; TYPE_1__* sk; } ;
struct tun_file {TYPE_3__ socket; int /*<<< orphan*/  tx_ring; } ;
struct TYPE_4__ {int sk_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EFAULT ; 
 int ERESTARTSYS ; 
 int RCV_SHUTDOWN ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 void* ptr_ring_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void *tun_ring_recv(struct tun_file *tfile, int noblock, int *err)
{
	DECLARE_WAITQUEUE(wait, current);
	void *ptr = NULL;
	int error = 0;

	ptr = ptr_ring_consume(&tfile->tx_ring);
	if (ptr)
		goto out;
	if (noblock) {
		error = -EAGAIN;
		goto out;
	}

	add_wait_queue(&tfile->socket.wq.wait, &wait);

	while (1) {
		set_current_state(TASK_INTERRUPTIBLE);
		ptr = ptr_ring_consume(&tfile->tx_ring);
		if (ptr)
			break;
		if (signal_pending(current)) {
			error = -ERESTARTSYS;
			break;
		}
		if (tfile->socket.sk->sk_shutdown & RCV_SHUTDOWN) {
			error = -EFAULT;
			break;
		}

		schedule();
	}

	__set_current_state(TASK_RUNNING);
	remove_wait_queue(&tfile->socket.wq.wait, &wait);

out:
	*err = error;
	return ptr;
}