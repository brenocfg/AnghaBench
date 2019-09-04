#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nports; } ;
struct rvt_dev_info {TYPE_3__** ports; TYPE_1__ dparms; } ;
struct TYPE_5__ {scalar_t__ rb_node; } ;
struct TYPE_6__ {TYPE_2__ mcast_tree; } ;

/* Variables and functions */

int rvt_mcast_tree_empty(struct rvt_dev_info *rdi)
{
	int i;
	int in_use = 0;

	for (i = 0; i < rdi->dparms.nports; i++)
		if (rdi->ports[i]->mcast_tree.rb_node)
			in_use++;
	return in_use;
}