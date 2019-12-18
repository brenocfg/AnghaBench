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
struct hns_roce_buf_region {int hopnum; int offset; int count; } ;

/* Variables and functions */
 int HNS_ROCE_HOP_NUM_0 ; 

void hns_roce_init_buf_region(struct hns_roce_buf_region *region, int hopnum,
			      int offset, int buf_cnt)
{
	if (hopnum == HNS_ROCE_HOP_NUM_0)
		region->hopnum = 0;
	else
		region->hopnum = hopnum;

	region->offset = offset;
	region->count = buf_cnt;
}