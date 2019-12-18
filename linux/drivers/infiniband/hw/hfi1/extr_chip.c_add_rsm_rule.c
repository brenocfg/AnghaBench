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
typedef  int u8 ;
typedef  unsigned long long u64 ;
struct rsm_rule_data {scalar_t__ value2; scalar_t__ mask2; scalar_t__ value1; scalar_t__ mask1; scalar_t__ index2_width; scalar_t__ index2_off; scalar_t__ index1_width; scalar_t__ index1_off; scalar_t__ field2_off; scalar_t__ field1_off; scalar_t__ pkt_type; scalar_t__ offset; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ RCV_RSM_CFG ; 
 unsigned long long RCV_RSM_CFG_OFFSET_SHIFT ; 
 unsigned long long RCV_RSM_CFG_PACKET_TYPE_SHIFT ; 
 scalar_t__ RCV_RSM_MATCH ; 
 unsigned long long RCV_RSM_MATCH_MASK1_SHIFT ; 
 unsigned long long RCV_RSM_MATCH_MASK2_SHIFT ; 
 unsigned long long RCV_RSM_MATCH_VALUE1_SHIFT ; 
 unsigned long long RCV_RSM_MATCH_VALUE2_SHIFT ; 
 scalar_t__ RCV_RSM_SELECT ; 
 unsigned long long RCV_RSM_SELECT_FIELD1_OFFSET_SHIFT ; 
 unsigned long long RCV_RSM_SELECT_FIELD2_OFFSET_SHIFT ; 
 unsigned long long RCV_RSM_SELECT_INDEX1_OFFSET_SHIFT ; 
 unsigned long long RCV_RSM_SELECT_INDEX1_WIDTH_SHIFT ; 
 unsigned long long RCV_RSM_SELECT_INDEX2_OFFSET_SHIFT ; 
 unsigned long long RCV_RSM_SELECT_INDEX2_WIDTH_SHIFT ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,unsigned long long) ; 

__attribute__((used)) static void add_rsm_rule(struct hfi1_devdata *dd, u8 rule_index,
			 struct rsm_rule_data *rrd)
{
	write_csr(dd, RCV_RSM_CFG + (8 * rule_index),
		  (u64)rrd->offset << RCV_RSM_CFG_OFFSET_SHIFT |
		  1ull << rule_index | /* enable bit */
		  (u64)rrd->pkt_type << RCV_RSM_CFG_PACKET_TYPE_SHIFT);
	write_csr(dd, RCV_RSM_SELECT + (8 * rule_index),
		  (u64)rrd->field1_off << RCV_RSM_SELECT_FIELD1_OFFSET_SHIFT |
		  (u64)rrd->field2_off << RCV_RSM_SELECT_FIELD2_OFFSET_SHIFT |
		  (u64)rrd->index1_off << RCV_RSM_SELECT_INDEX1_OFFSET_SHIFT |
		  (u64)rrd->index1_width << RCV_RSM_SELECT_INDEX1_WIDTH_SHIFT |
		  (u64)rrd->index2_off << RCV_RSM_SELECT_INDEX2_OFFSET_SHIFT |
		  (u64)rrd->index2_width << RCV_RSM_SELECT_INDEX2_WIDTH_SHIFT);
	write_csr(dd, RCV_RSM_MATCH + (8 * rule_index),
		  (u64)rrd->mask1 << RCV_RSM_MATCH_MASK1_SHIFT |
		  (u64)rrd->value1 << RCV_RSM_MATCH_VALUE1_SHIFT |
		  (u64)rrd->mask2 << RCV_RSM_MATCH_MASK2_SHIFT |
		  (u64)rrd->value2 << RCV_RSM_MATCH_VALUE2_SHIFT);
}