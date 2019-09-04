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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IPC_TX_MBOX ; 
 int __ipc_rcv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __ipc_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_completion ; 
 int /*<<< orphan*/  ipc_m1_lock ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int pl320_ipc_transmit(u32 *data)
{
	int ret;

	mutex_lock(&ipc_m1_lock);

	init_completion(&ipc_completion);
	__ipc_send(IPC_TX_MBOX, data);
	ret = wait_for_completion_timeout(&ipc_completion,
					  msecs_to_jiffies(1000));
	if (ret == 0) {
		ret = -ETIMEDOUT;
		goto out;
	}

	ret = __ipc_rcv(IPC_TX_MBOX, data);
out:
	mutex_unlock(&ipc_m1_lock);
	return ret;
}