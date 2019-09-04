#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union dm_mem_page_range {int dummy; } dm_mem_page_range ;
struct hv_dynmem_device {unsigned int num_pages_ballooned; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  type; } ;
struct dm_unballoon_response {TYPE_1__ hdr; } ;
struct dm_unballoon_request {int range_count; int more_pages; union dm_mem_page_range* range_array; } ;
struct TYPE_6__ {TYPE_2__* dev; int /*<<< orphan*/  config_event; } ;
struct TYPE_5__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_INITIALIZED ; 
 int /*<<< orphan*/  DM_UNBALLOON_RESPONSE ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_3__ dm_device ; 
 int /*<<< orphan*/  free_balloon_pages (struct hv_dynmem_device*,union dm_mem_page_range*) ; 
 int /*<<< orphan*/  memset (struct dm_unballoon_response*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  trans_id ; 
 int /*<<< orphan*/  vmbus_sendpacket (int /*<<< orphan*/ ,struct dm_unballoon_response*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balloon_down(struct hv_dynmem_device *dm,
			struct dm_unballoon_request *req)
{
	union dm_mem_page_range *range_array = req->range_array;
	int range_count = req->range_count;
	struct dm_unballoon_response resp;
	int i;
	unsigned int prev_pages_ballooned = dm->num_pages_ballooned;

	for (i = 0; i < range_count; i++) {
		free_balloon_pages(dm, &range_array[i]);
		complete(&dm_device.config_event);
	}

	pr_debug("Freed %u ballooned pages.\n",
		prev_pages_ballooned - dm->num_pages_ballooned);

	if (req->more_pages == 1)
		return;

	memset(&resp, 0, sizeof(struct dm_unballoon_response));
	resp.hdr.type = DM_UNBALLOON_RESPONSE;
	resp.hdr.trans_id = atomic_inc_return(&trans_id);
	resp.hdr.size = sizeof(struct dm_unballoon_response);

	vmbus_sendpacket(dm_device.dev->channel, &resp,
				sizeof(struct dm_unballoon_response),
				(unsigned long)NULL,
				VM_PKT_DATA_INBAND, 0);

	dm->state = DM_INITIALIZED;
}