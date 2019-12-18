#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  type; } ;
struct dm_balloon_response {int more_pages; int range_count; int /*<<< orphan*/ * range_array; TYPE_3__ hdr; } ;
struct TYPE_8__ {unsigned int num_pages; } ;
struct TYPE_11__ {TYPE_2__* dev; int /*<<< orphan*/  state; TYPE_1__ balloon_wrk; } ;
struct TYPE_9__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_BALLOON_RESPONSE ; 
 int /*<<< orphan*/  DM_INITIALIZED ; 
 int EAGAIN ; 
 unsigned int PAGES_IN_2M ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 unsigned int alloc_balloon_pages (TYPE_4__*,unsigned int,struct dm_balloon_response*,int) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ balloon_up_send_buffer ; 
 unsigned long compute_balloon_floor () ; 
 TYPE_4__ dm_device ; 
 int /*<<< orphan*/  free_balloon_pages (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  post_status (TYPE_4__*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 long si_mem_available () ; 
 int /*<<< orphan*/  trans_id ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,struct dm_balloon_response*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balloon_up(struct work_struct *dummy)
{
	unsigned int num_pages = dm_device.balloon_wrk.num_pages;
	unsigned int num_ballooned = 0;
	struct dm_balloon_response *bl_resp;
	int alloc_unit;
	int ret;
	bool done = false;
	int i;
	long avail_pages;
	unsigned long floor;

	/* The host balloons pages in 2M granularity. */
	WARN_ON_ONCE(num_pages % PAGES_IN_2M != 0);

	/*
	 * We will attempt 2M allocations. However, if we fail to
	 * allocate 2M chunks, we will go back to 4k allocations.
	 */
	alloc_unit = 512;

	avail_pages = si_mem_available();
	floor = compute_balloon_floor();

	/* Refuse to balloon below the floor, keep the 2M granularity. */
	if (avail_pages < num_pages || avail_pages - num_pages < floor) {
		pr_warn("Balloon request will be partially fulfilled. %s\n",
			avail_pages < num_pages ? "Not enough memory." :
			"Balloon floor reached.");

		num_pages = avail_pages > floor ? (avail_pages - floor) : 0;
		num_pages -= num_pages % PAGES_IN_2M;
	}

	while (!done) {
		memset(balloon_up_send_buffer, 0, PAGE_SIZE);
		bl_resp = (struct dm_balloon_response *)balloon_up_send_buffer;
		bl_resp->hdr.type = DM_BALLOON_RESPONSE;
		bl_resp->hdr.size = sizeof(struct dm_balloon_response);
		bl_resp->more_pages = 1;

		num_pages -= num_ballooned;
		num_ballooned = alloc_balloon_pages(&dm_device, num_pages,
						    bl_resp, alloc_unit);

		if (alloc_unit != 1 && num_ballooned == 0) {
			alloc_unit = 1;
			continue;
		}

		if (num_ballooned == 0 || num_ballooned == num_pages) {
			pr_debug("Ballooned %u out of %u requested pages.\n",
				num_pages, dm_device.balloon_wrk.num_pages);

			bl_resp->more_pages = 0;
			done = true;
			dm_device.state = DM_INITIALIZED;
		}

		/*
		 * We are pushing a lot of data through the channel;
		 * deal with transient failures caused because of the
		 * lack of space in the ring buffer.
		 */

		do {
			bl_resp->hdr.trans_id = atomic_inc_return(&trans_id);
			ret = vmbus_sendpacket(dm_device.dev->channel,
						bl_resp,
						bl_resp->hdr.size,
						(unsigned long)NULL,
						VM_PKT_DATA_INBAND, 0);

			if (ret == -EAGAIN)
				msleep(20);
			post_status(&dm_device);
		} while (ret == -EAGAIN);

		if (ret) {
			/*
			 * Free up the memory we allocatted.
			 */
			pr_err("Balloon response failed\n");

			for (i = 0; i < bl_resp->range_count; i++)
				free_balloon_pages(&dm_device,
						 &bl_resp->range_array[i]);

			done = true;
		}
	}

}