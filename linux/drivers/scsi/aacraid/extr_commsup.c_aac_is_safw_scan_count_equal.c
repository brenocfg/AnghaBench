#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct aac_dev {scalar_t__ scan_counter; TYPE_1__** hba_map; } ;
struct TYPE_2__ {scalar_t__ scan_counter; } ;

/* Variables and functions */

__attribute__((used)) static inline int aac_is_safw_scan_count_equal(struct aac_dev *dev,
	int bus, int target)
{
	return dev->hba_map[bus][target].scan_counter == dev->scan_counter;
}