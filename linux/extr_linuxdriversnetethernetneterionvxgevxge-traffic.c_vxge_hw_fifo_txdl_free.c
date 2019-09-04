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
typedef  int /*<<< orphan*/  u32 ;
struct vxge_hw_fifo_txd {int dummy; } ;
struct __vxge_hw_fifo_txdl_priv {int dummy; } ;
struct __vxge_hw_channel {int dummy; } ;
struct __vxge_hw_fifo {TYPE_1__* config; struct __vxge_hw_channel channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_frags; } ;

/* Variables and functions */
 struct __vxge_hw_fifo_txdl_priv* __vxge_hw_fifo_txdl_priv (struct __vxge_hw_fifo*,struct vxge_hw_fifo_txd*) ; 
 int /*<<< orphan*/  vxge_hw_channel_dtr_free (struct __vxge_hw_channel*,void*) ; 

void vxge_hw_fifo_txdl_free(struct __vxge_hw_fifo *fifo, void *txdlh)
{
	struct __vxge_hw_fifo_txdl_priv *txdl_priv;
	u32 max_frags;
	struct __vxge_hw_channel *channel;

	channel = &fifo->channel;

	txdl_priv = __vxge_hw_fifo_txdl_priv(fifo,
			(struct vxge_hw_fifo_txd *)txdlh);

	max_frags = fifo->config->max_frags;

	vxge_hw_channel_dtr_free(channel, txdlh);
}