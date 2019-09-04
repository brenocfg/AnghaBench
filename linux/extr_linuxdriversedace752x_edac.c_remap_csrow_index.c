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
struct mem_ctl_info {struct e752x_pvt* pvt_info; } ;
struct e752x_pvt {int /*<<< orphan*/  map_type; } ;

/* Variables and functions */

__attribute__((used)) static inline int remap_csrow_index(struct mem_ctl_info *mci, int index)
{
	struct e752x_pvt *pvt = mci->pvt_info;

	if (!pvt->map_type)
		return (7 - index);

	return (index);
}