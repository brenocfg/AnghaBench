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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct ionic_lif {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_strings ) (struct ionic_lif*,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 size_t ionic_num_stats_grps ; 
 TYPE_1__* ionic_stats_groups ; 
 int /*<<< orphan*/  stub1 (struct ionic_lif*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void ionic_get_stats_strings(struct ionic_lif *lif, u8 *buf)
{
	u32 i;

	for (i = 0; i < ionic_num_stats_grps; i++)
		ionic_stats_groups[i].get_strings(lif, &buf);
}