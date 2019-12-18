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
struct qcom_smd_channel {int fifo_size; } ;

/* Variables and functions */
 unsigned int GET_TX_CHANNEL_INFO (struct qcom_smd_channel*,unsigned int) ; 

__attribute__((used)) static size_t qcom_smd_get_tx_avail(struct qcom_smd_channel *channel)
{
	unsigned head;
	unsigned tail;
	unsigned mask = channel->fifo_size - 1;

	head = GET_TX_CHANNEL_INFO(channel, head);
	tail = GET_TX_CHANNEL_INFO(channel, tail);

	return mask - ((head - tail) & mask);
}