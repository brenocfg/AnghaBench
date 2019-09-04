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
typedef  int /*<<< orphan*/  u32 ;
struct list_head {int dummy; } ;
struct char_queue {int /*<<< orphan*/  list; int /*<<< orphan*/  msg; } ;
struct TYPE_4__ {int /*<<< orphan*/  async_queue; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; TYPE_1__* cl; int /*<<< orphan*/  opened; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 TYPE_2__ cs_char_data ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct char_queue* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cs_notify(u32 message, struct list_head *head)
{
	struct char_queue *entry;

	spin_lock(&cs_char_data.lock);

	if (!cs_char_data.opened) {
		spin_unlock(&cs_char_data.lock);
		goto out;
	}

	entry = kmalloc(sizeof(*entry), GFP_ATOMIC);
	if (!entry) {
		dev_err(&cs_char_data.cl->device,
			"Can't allocate new entry for the queue.\n");
		spin_unlock(&cs_char_data.lock);
		goto out;
	}

	entry->msg = message;
	list_add_tail(&entry->list, head);

	spin_unlock(&cs_char_data.lock);

	wake_up_interruptible(&cs_char_data.wait);
	kill_fasync(&cs_char_data.async_queue, SIGIO, POLL_IN);

out:
	return;
}