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
typedef  int u32 ;

/* Variables and functions */
 int RTK_BEQ_TX_DESC_NUM ; 
 int RTK_DEFAULT_TX_DESC_NUM ; 
#define  RTW_TX_QUEUE_BCN 129 
#define  RTW_TX_QUEUE_BE 128 

__attribute__((used)) static u32 max_num_of_tx_queue(u8 queue)
{
	u32 max_num;

	switch (queue) {
	case RTW_TX_QUEUE_BE:
		max_num = RTK_BEQ_TX_DESC_NUM;
		break;
	case RTW_TX_QUEUE_BCN:
		max_num = 1;
		break;
	default:
		max_num = RTK_DEFAULT_TX_DESC_NUM;
		break;
	}

	return max_num;
}