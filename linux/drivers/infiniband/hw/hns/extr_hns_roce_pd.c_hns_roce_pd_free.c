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
struct hns_roce_dev {int /*<<< orphan*/  pd_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_NO_RR ; 
 int /*<<< orphan*/  hns_roce_bitmap_free (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_pd_free(struct hns_roce_dev *hr_dev, unsigned long pdn)
{
	hns_roce_bitmap_free(&hr_dev->pd_bitmap, pdn, BITMAP_NO_RR);
}