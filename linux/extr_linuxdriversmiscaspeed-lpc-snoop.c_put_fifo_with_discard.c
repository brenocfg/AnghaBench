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
typedef  int /*<<< orphan*/  u8 ;
struct aspeed_lpc_snoop_channel {int /*<<< orphan*/  wq; int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfifo_initialized (int /*<<< orphan*/ *) ; 
 scalar_t__ kfifo_is_full (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_skip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_fifo_with_discard(struct aspeed_lpc_snoop_channel *chan, u8 val)
{
	if (!kfifo_initialized(&chan->fifo))
		return;
	if (kfifo_is_full(&chan->fifo))
		kfifo_skip(&chan->fifo);
	kfifo_put(&chan->fifo, val);
	wake_up_interruptible(&chan->wq);
}