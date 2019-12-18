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
typedef  enum hinic_msix_state { ____Placeholder_hinic_msix_state } hinic_msix_state ;

/* Variables and functions */
 int /*<<< orphan*/  hinic_set_msix_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void hinic_hwdev_set_msix_state(struct hinic_hwdev *hwdev, u16 msix_index,
				enum hinic_msix_state flag)
{
	hinic_set_msix_state(hwdev->hwif, msix_index, flag);
}