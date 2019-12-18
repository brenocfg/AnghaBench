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
struct poll_table_struct {int dummy; } ;
struct file {struct ca8210_priv* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  up_fifo; int /*<<< orphan*/  readq; } ;
struct ca8210_priv {TYPE_1__ test; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __poll_t ca8210_test_int_poll(
	struct file *filp,
	struct poll_table_struct *ptable
)
{
	__poll_t return_flags = 0;
	struct ca8210_priv *priv = filp->private_data;

	poll_wait(filp, &priv->test.readq, ptable);
	if (!kfifo_is_empty(&priv->test.up_fifo))
		return_flags |= (EPOLLIN | EPOLLRDNORM);
	if (wait_event_interruptible(
		priv->test.readq,
		!kfifo_is_empty(&priv->test.up_fifo))) {
		return EPOLLERR;
	}
	return return_flags;
}