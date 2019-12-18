#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct TYPE_10__ {unsigned long start_page; unsigned long page_cnt; } ;
struct TYPE_11__ {TYPE_3__ finfo; } ;
struct TYPE_8__ {unsigned long start_page; unsigned long page_cnt; } ;
struct TYPE_9__ {TYPE_1__ finfo; } ;
struct TYPE_12__ {TYPE_4__ ha_region_range; TYPE_2__ ha_page_range; } ;
struct hv_dynmem_device {TYPE_7__* dev; int /*<<< orphan*/  state; int /*<<< orphan*/  num_pages_added; int /*<<< orphan*/  host_specified_ha_region; TYPE_5__ ha_wrk; } ;
struct TYPE_13__ {int size; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  type; } ;
struct dm_hot_add_response {scalar_t__ page_count; int result; TYPE_6__ hdr; } ;
struct TYPE_14__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_INITIALIZED ; 
 int /*<<< orphan*/  DM_MEM_HOT_ADD_RESPONSE ; 
 unsigned long HA_CHUNK ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 struct hv_dynmem_device dm_device ; 
 scalar_t__ do_hot_add ; 
 int /*<<< orphan*/  memset (struct dm_hot_add_response*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ process_hot_add (unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  trans_id ; 
 int /*<<< orphan*/  vmbus_sendpacket (int /*<<< orphan*/ ,struct dm_hot_add_response*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hot_add_req(struct work_struct *dummy)
{
	struct dm_hot_add_response resp;
#ifdef CONFIG_MEMORY_HOTPLUG
	unsigned long pg_start, pfn_cnt;
	unsigned long rg_start, rg_sz;
#endif
	struct hv_dynmem_device *dm = &dm_device;

	memset(&resp, 0, sizeof(struct dm_hot_add_response));
	resp.hdr.type = DM_MEM_HOT_ADD_RESPONSE;
	resp.hdr.size = sizeof(struct dm_hot_add_response);

#ifdef CONFIG_MEMORY_HOTPLUG
	pg_start = dm->ha_wrk.ha_page_range.finfo.start_page;
	pfn_cnt = dm->ha_wrk.ha_page_range.finfo.page_cnt;

	rg_start = dm->ha_wrk.ha_region_range.finfo.start_page;
	rg_sz = dm->ha_wrk.ha_region_range.finfo.page_cnt;

	if ((rg_start == 0) && (!dm->host_specified_ha_region)) {
		unsigned long region_size;
		unsigned long region_start;

		/*
		 * The host has not specified the hot-add region.
		 * Based on the hot-add page range being specified,
		 * compute a hot-add region that can cover the pages
		 * that need to be hot-added while ensuring the alignment
		 * and size requirements of Linux as it relates to hot-add.
		 */
		region_start = pg_start;
		region_size = (pfn_cnt / HA_CHUNK) * HA_CHUNK;
		if (pfn_cnt % HA_CHUNK)
			region_size += HA_CHUNK;

		region_start = (pg_start / HA_CHUNK) * HA_CHUNK;

		rg_start = region_start;
		rg_sz = region_size;
	}

	if (do_hot_add)
		resp.page_count = process_hot_add(pg_start, pfn_cnt,
						rg_start, rg_sz);

	dm->num_pages_added += resp.page_count;
#endif
	/*
	 * The result field of the response structure has the
	 * following semantics:
	 *
	 * 1. If all or some pages hot-added: Guest should return success.
	 *
	 * 2. If no pages could be hot-added:
	 *
	 * If the guest returns success, then the host
	 * will not attempt any further hot-add operations. This
	 * signifies a permanent failure.
	 *
	 * If the guest returns failure, then this failure will be
	 * treated as a transient failure and the host may retry the
	 * hot-add operation after some delay.
	 */
	if (resp.page_count > 0)
		resp.result = 1;
	else if (!do_hot_add)
		resp.result = 1;
	else
		resp.result = 0;

	if (!do_hot_add || (resp.page_count == 0))
		pr_err("Memory hot add failed\n");

	dm->state = DM_INITIALIZED;
	resp.hdr.trans_id = atomic_inc_return(&trans_id);
	vmbus_sendpacket(dm->dev->channel, &resp,
			sizeof(struct dm_hot_add_response),
			(unsigned long)NULL,
			VM_PKT_DATA_INBAND, 0);
}