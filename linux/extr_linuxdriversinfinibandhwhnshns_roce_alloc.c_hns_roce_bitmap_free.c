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
struct hns_roce_bitmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_bitmap_free_range (struct hns_roce_bitmap*,unsigned long,int,int) ; 

void hns_roce_bitmap_free(struct hns_roce_bitmap *bitmap, unsigned long obj,
			  int rr)
{
	hns_roce_bitmap_free_range(bitmap, obj, 1, rr);
}