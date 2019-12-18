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
struct hv_dynmem_device {scalar_t__ num_pages_added; scalar_t__ num_pages_onlined; TYPE_2__* dev; scalar_t__ num_pages_ballooned; } ;
struct TYPE_3__ {int size; scalar_t__ trans_id; int /*<<< orphan*/  type; } ;
struct dm_status {TYPE_1__ hdr; scalar_t__ num_committed; int /*<<< orphan*/  num_avail; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_STATUS_REPORT ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ compute_balloon_floor () ; 
 unsigned long jiffies ; 
 unsigned long last_post_time ; 
 int /*<<< orphan*/  memset (struct dm_status*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pressure_report_delay ; 
 int /*<<< orphan*/  si_mem_available () ; 
 int /*<<< orphan*/  time_after (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  trace_balloon_status (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trans_id ; 
 scalar_t__ vm_memory_committed () ; 
 int /*<<< orphan*/  vmbus_sendpacket (int /*<<< orphan*/ ,struct dm_status*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void post_status(struct hv_dynmem_device *dm)
{
	struct dm_status status;
	unsigned long now = jiffies;
	unsigned long last_post = last_post_time;

	if (pressure_report_delay > 0) {
		--pressure_report_delay;
		return;
	}

	if (!time_after(now, (last_post_time + HZ)))
		return;

	memset(&status, 0, sizeof(struct dm_status));
	status.hdr.type = DM_STATUS_REPORT;
	status.hdr.size = sizeof(struct dm_status);
	status.hdr.trans_id = atomic_inc_return(&trans_id);

	/*
	 * The host expects the guest to report free and committed memory.
	 * Furthermore, the host expects the pressure information to include
	 * the ballooned out pages. For a given amount of memory that we are
	 * managing we need to compute a floor below which we should not
	 * balloon. Compute this and add it to the pressure report.
	 * We also need to report all offline pages (num_pages_added -
	 * num_pages_onlined) as committed to the host, otherwise it can try
	 * asking us to balloon them out.
	 */
	status.num_avail = si_mem_available();
	status.num_committed = vm_memory_committed() +
		dm->num_pages_ballooned +
		(dm->num_pages_added > dm->num_pages_onlined ?
		 dm->num_pages_added - dm->num_pages_onlined : 0) +
		compute_balloon_floor();

	trace_balloon_status(status.num_avail, status.num_committed,
			     vm_memory_committed(), dm->num_pages_ballooned,
			     dm->num_pages_added, dm->num_pages_onlined);
	/*
	 * If our transaction ID is no longer current, just don't
	 * send the status. This can happen if we were interrupted
	 * after we picked our transaction ID.
	 */
	if (status.hdr.trans_id != atomic_read(&trans_id))
		return;

	/*
	 * If the last post time that we sampled has changed,
	 * we have raced, don't post the status.
	 */
	if (last_post != last_post_time)
		return;

	last_post_time = jiffies;
	vmbus_sendpacket(dm->dev->channel, &status,
				sizeof(struct dm_status),
				(unsigned long)NULL,
				VM_PKT_DATA_INBAND, 0);

}