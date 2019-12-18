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
struct rc_dev {int idle; TYPE_1__* raw; int /*<<< orphan*/  change_protocol; } ;
struct TYPE_2__ {int /*<<< orphan*/  kfifo; int /*<<< orphan*/  edge_handle; int /*<<< orphan*/  edge_spinlock; struct rc_dev* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_KFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_protocol ; 
 int /*<<< orphan*/  ir_raw_edge_handle ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ir_raw_event_prepare(struct rc_dev *dev)
{
	if (!dev)
		return -EINVAL;

	dev->raw = kzalloc(sizeof(*dev->raw), GFP_KERNEL);
	if (!dev->raw)
		return -ENOMEM;

	dev->raw->dev = dev;
	dev->change_protocol = change_protocol;
	dev->idle = true;
	spin_lock_init(&dev->raw->edge_spinlock);
	timer_setup(&dev->raw->edge_handle, ir_raw_edge_handle, 0);
	INIT_KFIFO(dev->raw->kfifo);

	return 0;
}