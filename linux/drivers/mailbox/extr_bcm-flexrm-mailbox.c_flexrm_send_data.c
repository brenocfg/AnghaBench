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
struct mbox_chan {struct flexrm_ring* con_priv; } ;
struct flexrm_ring {int dummy; } ;
struct TYPE_2__ {int msgs_queued; int msgs_count; void* msgs; } ;
struct brcm_message {scalar_t__ type; int error; TYPE_1__ batch; } ;

/* Variables and functions */
 scalar_t__ BRCM_MESSAGE_BATCH ; 
 int flexrm_new_request (struct flexrm_ring*,struct brcm_message*,void*) ; 

__attribute__((used)) static int flexrm_send_data(struct mbox_chan *chan, void *data)
{
	int i, rc;
	struct flexrm_ring *ring = chan->con_priv;
	struct brcm_message *msg = data;

	if (msg->type == BRCM_MESSAGE_BATCH) {
		for (i = msg->batch.msgs_queued;
		     i < msg->batch.msgs_count; i++) {
			rc = flexrm_new_request(ring, msg,
						 &msg->batch.msgs[i]);
			if (rc) {
				msg->error = rc;
				return rc;
			}
			msg->batch.msgs_queued++;
		}
		return 0;
	}

	return flexrm_new_request(ring, NULL, data);
}