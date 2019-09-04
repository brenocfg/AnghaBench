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
struct uhid_event {int /*<<< orphan*/  type; } ;
struct uhid_device {int /*<<< orphan*/  qlock; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct uhid_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uhid_queue (struct uhid_device*,struct uhid_event*) ; 

__attribute__((used)) static int uhid_queue_event(struct uhid_device *uhid, __u32 event)
{
	unsigned long flags;
	struct uhid_event *ev;

	ev = kzalloc(sizeof(*ev), GFP_KERNEL);
	if (!ev)
		return -ENOMEM;

	ev->type = event;

	spin_lock_irqsave(&uhid->qlock, flags);
	uhid_queue(uhid, ev);
	spin_unlock_irqrestore(&uhid->qlock, flags);

	return 0;
}