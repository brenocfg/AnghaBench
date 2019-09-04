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
typedef  size_t u32 ;
struct hclge_pkt_buf_alloc {TYPE_1__* priv_buf; } ;
struct TYPE_2__ {scalar_t__ tx_buf_size; } ;

/* Variables and functions */
 size_t HCLGE_MAX_TC_NUM ; 

__attribute__((used)) static u32 hclge_get_tx_buff_alloced(struct hclge_pkt_buf_alloc *buf_alloc)
{
	u32 i, total_tx_size = 0;

	for (i = 0; i < HCLGE_MAX_TC_NUM; i++)
		total_tx_size += buf_alloc->priv_buf[i].tx_buf_size;

	return total_tx_size;
}