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
typedef  int u32 ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int map_capacity; } ;
struct cw1200_common {TYPE_1__ tx_queue_stats; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void cw1200_debug_print_map(struct seq_file *seq,
				   struct cw1200_common *priv,
				   const char *label,
				   u32 map)
{
	int i;
	seq_printf(seq, "%s0-> ", label);
	for (i = 0; i < priv->tx_queue_stats.map_capacity; ++i)
		seq_printf(seq, "%s ", (map & BIT(i)) ? "**" : "..");
	seq_printf(seq, "<-%zu\n", priv->tx_queue_stats.map_capacity - 1);
}