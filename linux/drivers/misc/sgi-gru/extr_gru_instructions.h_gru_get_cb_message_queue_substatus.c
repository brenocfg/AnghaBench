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
struct gru_control_block_status {int isubstatus; } ;

/* Variables and functions */
 int CBSS_MSG_QUEUE_MASK ; 

__attribute__((used)) static inline int gru_get_cb_message_queue_substatus(void *cb)
{
	struct gru_control_block_status *cbs = (void *)cb;

	return cbs->isubstatus & CBSS_MSG_QUEUE_MASK;
}