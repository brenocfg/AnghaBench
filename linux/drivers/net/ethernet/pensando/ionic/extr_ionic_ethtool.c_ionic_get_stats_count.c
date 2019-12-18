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
struct ionic_lif {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* get_count ) (struct ionic_lif*) ;} ;

/* Variables and functions */
 int ionic_num_stats_grps ; 
 TYPE_1__* ionic_stats_groups ; 
 scalar_t__ stub1 (struct ionic_lif*) ; 

__attribute__((used)) static int ionic_get_stats_count(struct ionic_lif *lif)
{
	int i, num_stats = 0;

	for (i = 0; i < ionic_num_stats_grps; i++)
		num_stats += ionic_stats_groups[i].get_count(lif);

	return num_stats;
}