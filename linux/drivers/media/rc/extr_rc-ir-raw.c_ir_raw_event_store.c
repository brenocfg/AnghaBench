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
struct rc_dev {int /*<<< orphan*/  dev; TYPE_1__* raw; } ;
struct ir_raw_event {int /*<<< orphan*/  pulse; int /*<<< orphan*/  duration; } ;
struct TYPE_2__ {int /*<<< orphan*/  kfifo; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  TO_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TO_US (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ *,struct ir_raw_event) ; 

int ir_raw_event_store(struct rc_dev *dev, struct ir_raw_event *ev)
{
	if (!dev->raw)
		return -EINVAL;

	dev_dbg(&dev->dev, "sample: (%05dus %s)\n",
		TO_US(ev->duration), TO_STR(ev->pulse));

	if (!kfifo_put(&dev->raw->kfifo, *ev)) {
		dev_err(&dev->dev, "IR event FIFO is full!\n");
		return -ENOSPC;
	}

	return 0;
}