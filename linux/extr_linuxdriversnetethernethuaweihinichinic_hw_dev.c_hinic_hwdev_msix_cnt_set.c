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
typedef  int /*<<< orphan*/  u16 ;
struct hinic_hwdev {int /*<<< orphan*/  hwif; } ;

/* Variables and functions */
 int hinic_msix_attr_cnt_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hinic_hwdev_msix_cnt_set(struct hinic_hwdev *hwdev, u16 msix_index)
{
	return hinic_msix_attr_cnt_clear(hwdev->hwif, msix_index);
}