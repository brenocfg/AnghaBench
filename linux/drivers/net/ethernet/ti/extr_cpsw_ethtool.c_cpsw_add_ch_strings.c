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
struct TYPE_2__ {int /*<<< orphan*/  stat_string; } ;

/* Variables and functions */
 int CPSW_STATS_CH_LEN ; 
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
 TYPE_1__* cpsw_gstrings_ch_stats ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpsw_add_ch_strings(u8 **p, int ch_num, int rx_dir)
{
	int ch_stats_len;
	int line;
	int i;

	ch_stats_len = CPSW_STATS_CH_LEN * ch_num;
	for (i = 0; i < ch_stats_len; i++) {
		line = i % CPSW_STATS_CH_LEN;
		snprintf(*p, ETH_GSTRING_LEN,
			 "%s DMA chan %ld: %s", rx_dir ? "Rx" : "Tx",
			 (long)(i / CPSW_STATS_CH_LEN),
			 cpsw_gstrings_ch_stats[line].stat_string);
		*p += ETH_GSTRING_LEN;
	}
}