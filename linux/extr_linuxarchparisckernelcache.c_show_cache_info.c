#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  num_comb; int /*<<< orphan*/  num_d; int /*<<< orphan*/  num_i; } ;
struct TYPE_9__ {int /*<<< orphan*/  num_comb; int /*<<< orphan*/  num_d; int /*<<< orphan*/  num_i; } ;
struct TYPE_12__ {int max_size; TYPE_4__ variable_range_info; TYPE_3__ fixed_range_info; } ;
struct TYPE_8__ {scalar_t__ tc_sh; } ;
struct TYPE_7__ {scalar_t__ cc_sh; scalar_t__ cc_wt; } ;
struct TYPE_11__ {int ic_size; int dc_loop; int dc_size; TYPE_2__ dt_conf; int /*<<< orphan*/  dt_size; int /*<<< orphan*/  it_size; TYPE_1__ dc_conf; } ;

/* Variables and functions */
 TYPE_6__ btlb_info ; 
 TYPE_5__ cache_info ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void
show_cache_info(struct seq_file *m)
{
	char buf[32];

	seq_printf(m, "I-cache\t\t: %ld KB\n", 
		cache_info.ic_size/1024 );
	if (cache_info.dc_loop != 1)
		snprintf(buf, 32, "%lu-way associative", cache_info.dc_loop);
	seq_printf(m, "D-cache\t\t: %ld KB (%s%s, %s)\n",
		cache_info.dc_size/1024,
		(cache_info.dc_conf.cc_wt ? "WT":"WB"),
		(cache_info.dc_conf.cc_sh ? ", shared I/D":""),
		((cache_info.dc_loop == 1) ? "direct mapped" : buf));
	seq_printf(m, "ITLB entries\t: %ld\n" "DTLB entries\t: %ld%s\n",
		cache_info.it_size,
		cache_info.dt_size,
		cache_info.dt_conf.tc_sh ? " - shared with ITLB":""
	);
		
#ifndef CONFIG_PA20
	/* BTLB - Block TLB */
	if (btlb_info.max_size==0) {
		seq_printf(m, "BTLB\t\t: not supported\n" );
	} else {
		seq_printf(m, 
		"BTLB fixed\t: max. %d pages, pagesize=%d (%dMB)\n"
		"BTLB fix-entr.\t: %d instruction, %d data (%d combined)\n"
		"BTLB var-entr.\t: %d instruction, %d data (%d combined)\n",
		btlb_info.max_size, (int)4096,
		btlb_info.max_size>>8,
		btlb_info.fixed_range_info.num_i,
		btlb_info.fixed_range_info.num_d,
		btlb_info.fixed_range_info.num_comb, 
		btlb_info.variable_range_info.num_i,
		btlb_info.variable_range_info.num_d,
		btlb_info.variable_range_info.num_comb
		);
	}
#endif
}