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
struct hclge_32_bit_stats {scalar_t__ pkt_curr_buf_tc7_cnt; scalar_t__ pkt_curr_buf_tc6_cnt; scalar_t__ pkt_curr_buf_tc5_cnt; scalar_t__ pkt_curr_buf_tc4_cnt; scalar_t__ pkt_curr_buf_tc3_cnt; scalar_t__ pkt_curr_buf_tc2_cnt; scalar_t__ pkt_curr_buf_tc1_cnt; scalar_t__ pkt_curr_buf_tc0_cnt; scalar_t__ pkt_curr_buf_cnt; } ;

/* Variables and functions */

__attribute__((used)) static void hclge_reset_partial_32bit_counter(struct hclge_32_bit_stats *stats)
{
	stats->pkt_curr_buf_cnt     = 0;
	stats->pkt_curr_buf_tc0_cnt = 0;
	stats->pkt_curr_buf_tc1_cnt = 0;
	stats->pkt_curr_buf_tc2_cnt = 0;
	stats->pkt_curr_buf_tc3_cnt = 0;
	stats->pkt_curr_buf_tc4_cnt = 0;
	stats->pkt_curr_buf_tc5_cnt = 0;
	stats->pkt_curr_buf_tc6_cnt = 0;
	stats->pkt_curr_buf_tc7_cnt = 0;
}