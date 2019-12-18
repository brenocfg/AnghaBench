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
typedef  scalar_t__ u64 ;
struct port_stats {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  t4_get_port_stats (struct adapter*,int,struct port_stats*) ; 

void t4_get_port_stats_offset(struct adapter *adap, int idx,
			      struct port_stats *stats,
			      struct port_stats *offset)
{
	u64 *s, *o;
	int i;

	t4_get_port_stats(adap, idx, stats);
	for (i = 0, s = (u64 *)stats, o = (u64 *)offset;
			i < (sizeof(struct port_stats) / sizeof(u64));
			i++, s++, o++)
		*s -= *o;
}