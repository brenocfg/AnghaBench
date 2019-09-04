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
typedef  scalar_t__ u32 ;
struct mei_txe_hw {scalar_t__ aliveness; } ;
struct mei_device {int /*<<< orphan*/  dev; void* pg_event; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int ETIME ; 
 void* MEI_PG_EVENT_IDLE ; 
 int /*<<< orphan*/  SEC_ALIVENESS_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_us (int /*<<< orphan*/ ) ; 
 scalar_t__ mei_txe_aliveness_get (struct mei_device*) ; 
 int /*<<< orphan*/  ms_to_ktime (int /*<<< orphan*/ ) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mei_txe_aliveness_poll(struct mei_device *dev, u32 expected)
{
	struct mei_txe_hw *hw = to_txe_hw(dev);
	ktime_t stop, start;

	start = ktime_get();
	stop = ktime_add(start, ms_to_ktime(SEC_ALIVENESS_WAIT_TIMEOUT));
	do {
		hw->aliveness = mei_txe_aliveness_get(dev);
		if (hw->aliveness == expected) {
			dev->pg_event = MEI_PG_EVENT_IDLE;
			dev_dbg(dev->dev, "aliveness settled after %lld usecs\n",
				ktime_to_us(ktime_sub(ktime_get(), start)));
			return 0;
		}
		usleep_range(20, 50);
	} while (ktime_before(ktime_get(), stop));

	dev->pg_event = MEI_PG_EVENT_IDLE;
	dev_err(dev->dev, "aliveness timed out\n");
	return -ETIME;
}