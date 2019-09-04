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
struct reader_dev {int /*<<< orphan*/  timeout; int /*<<< orphan*/  buffer_status; int /*<<< orphan*/  write_wait; TYPE_1__* p_dev; } ;
struct TYPE_4__ {int start; } ;
struct TYPE_3__ {TYPE_2__** resource; } ;

/* Variables and functions */
 int BSR_BULK_OUT_FULL ; 
 int /*<<< orphan*/  BS_WRITABLE ; 
 int /*<<< orphan*/  DEBUGP (int,struct reader_dev*,char*,...) ; 
 int POLL_LOOP_COUNT ; 
 scalar_t__ REG_OFFSET_BUFFER_STATUS ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xinb (scalar_t__) ; 

__attribute__((used)) static int wait_for_bulk_out_ready(struct reader_dev *dev)
{
	int i, rc;
	int iobase = dev->p_dev->resource[0]->start;

	for (i = 0; i < POLL_LOOP_COUNT; i++) {
		if ((xinb(iobase + REG_OFFSET_BUFFER_STATUS)
		    & BSR_BULK_OUT_FULL) == 0) {
			DEBUGP(4, dev, "BulkOut empty (i=%d)\n", i);
			return 1;
		}
	}

	DEBUGP(4, dev, "wait_event_interruptible_timeout(timeout=%ld\n",
		dev->timeout);
	rc = wait_event_interruptible_timeout(dev->write_wait,
					      test_and_clear_bit(BS_WRITABLE,
						       &dev->buffer_status),
					      dev->timeout);

	if (rc > 0)
		DEBUGP(4, dev, "woke up: BulkOut empty\n");
	else if (rc == 0)
		DEBUGP(4, dev, "woke up: BulkOut full, returning 0 :(\n");
	else if (rc < 0)
		DEBUGP(4, dev, "woke up: signal arrived\n");

	return rc;
}