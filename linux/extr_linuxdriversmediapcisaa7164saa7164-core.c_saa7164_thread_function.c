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
typedef  scalar_t__ u64 ;
struct tmFwInfoStruct {int dummy; } ;
struct saa7164_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGLVL_THR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  saa7164_api_collect_debug (struct saa7164_dev*) ; 
 int /*<<< orphan*/  saa7164_api_get_load_info (struct saa7164_dev*,struct tmFwInfoStruct*) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  try_to_freeze () ; 

__attribute__((used)) static int saa7164_thread_function(void *data)
{
	struct saa7164_dev *dev = data;
	struct tmFwInfoStruct fwinfo;
	u64 last_poll_time = 0;

	dprintk(DBGLVL_THR, "thread started\n");

	set_freezable();

	while (1) {
		msleep_interruptible(100);
		if (kthread_should_stop())
			break;
		try_to_freeze();

		dprintk(DBGLVL_THR, "thread running\n");

		/* Dump the firmware debug message to console */
		/* Polling this costs us 1-2% of the arm CPU */
		/* convert this into a respnde to interrupt 0x7a */
		saa7164_api_collect_debug(dev);

		/* Monitor CPU load every 1 second */
		if ((last_poll_time + 1000 /* ms */) < jiffies_to_msecs(jiffies)) {
			saa7164_api_get_load_info(dev, &fwinfo);
			last_poll_time = jiffies_to_msecs(jiffies);
		}

	}

	dprintk(DBGLVL_THR, "thread exiting\n");
	return 0;
}