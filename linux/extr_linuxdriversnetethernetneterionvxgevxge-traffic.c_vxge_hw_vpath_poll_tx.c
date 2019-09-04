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
struct sk_buff {int dummy; } ;
struct __vxge_hw_channel {int /*<<< orphan*/  userdata; } ;
struct __vxge_hw_fifo {int (* callback ) (struct __vxge_hw_fifo*,void*,int,int /*<<< orphan*/ ,struct sk_buff***,int,int*) ;struct __vxge_hw_channel channel; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
typedef  enum vxge_hw_fifo_tcode { ____Placeholder_vxge_hw_fifo_tcode } vxge_hw_fifo_tcode ;

/* Variables and functions */
 int VXGE_HW_COMPLETIONS_REMAIN ; 
 int VXGE_HW_OK ; 
 int stub1 (struct __vxge_hw_fifo*,void*,int,int /*<<< orphan*/ ,struct sk_buff***,int,int*) ; 
 int vxge_hw_fifo_txdl_next_completed (struct __vxge_hw_fifo*,void**,int*) ; 

enum vxge_hw_status vxge_hw_vpath_poll_tx(struct __vxge_hw_fifo *fifo,
					struct sk_buff ***skb_ptr, int nr_skb,
					int *more)
{
	enum vxge_hw_fifo_tcode t_code;
	void *first_txdlh;
	enum vxge_hw_status status = VXGE_HW_OK;
	struct __vxge_hw_channel *channel;

	channel = &fifo->channel;

	status = vxge_hw_fifo_txdl_next_completed(fifo,
				&first_txdlh, &t_code);
	if (status == VXGE_HW_OK)
		if (fifo->callback(fifo, first_txdlh, t_code,
			channel->userdata, skb_ptr, nr_skb, more) != VXGE_HW_OK)
			status = VXGE_HW_COMPLETIONS_REMAIN;

	return status;
}