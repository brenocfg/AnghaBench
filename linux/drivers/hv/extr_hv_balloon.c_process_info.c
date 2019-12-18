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
struct hv_dynmem_device {int dummy; } ;
struct dm_info_msg {scalar_t__ info; } ;
struct dm_info_header {int type; int data_size; } ;
typedef  int __u64 ;

/* Variables and functions */
#define  INFO_TYPE_MAX_PAGE_CNT 128 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static void process_info(struct hv_dynmem_device *dm, struct dm_info_msg *msg)
{
	struct dm_info_header *info_hdr;

	info_hdr = (struct dm_info_header *)msg->info;

	switch (info_hdr->type) {
	case INFO_TYPE_MAX_PAGE_CNT:
		if (info_hdr->data_size == sizeof(__u64)) {
			__u64 *max_page_count = (__u64 *)&info_hdr[1];

			pr_info("Max. dynamic memory size: %llu MB\n",
				(*max_page_count) >> (20 - PAGE_SHIFT));
		}

		break;
	default:
		pr_warn("Received Unknown type: %d\n", info_hdr->type);
	}
}