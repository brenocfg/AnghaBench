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
struct TYPE_2__ {int max_bdi; int num_bds_table; } ;
struct bdc_ep {TYPE_1__ bd_list; } ;

/* Variables and functions */

__attribute__((used)) static inline int find_end_bdi(struct bdc_ep *ep, int next_hwd_bdi)
{
	int end_bdi;

	end_bdi = next_hwd_bdi - 1;
	if (end_bdi < 0)
		end_bdi = ep->bd_list.max_bdi - 1;
	 else if ((end_bdi % (ep->bd_list.num_bds_table-1)) == 0)
		end_bdi--;

	return end_bdi;
}