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
struct __vxge_hw_channel {int dummy; } ;
struct __vxge_hw_fifo {struct __vxge_hw_channel channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  vxge_hw_channel_dtr_free (struct __vxge_hw_channel*,void*) ; 

void vxge_hw_fifo_txdl_free(struct __vxge_hw_fifo *fifo, void *txdlh)
{
	struct __vxge_hw_channel *channel;

	channel = &fifo->channel;

	vxge_hw_channel_dtr_free(channel, txdlh);
}