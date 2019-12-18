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
struct wsm_tx_confirm {void* tx_queue_delay; void* media_delay; int /*<<< orphan*/  flags; void* ack_failures; void* tx_rate; void* status; void* packet_id; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WSM_GET16 (struct wsm_buf*) ; 
 void* WSM_GET32 (struct wsm_buf*) ; 
 void* WSM_GET8 (struct wsm_buf*) ; 
 int /*<<< orphan*/  cw1200_tx_confirm_cb (struct cw1200_common*,int,struct wsm_tx_confirm*) ; 

__attribute__((used)) static int wsm_tx_confirm(struct cw1200_common *priv,
			  struct wsm_buf *buf,
			  int link_id)
{
	struct wsm_tx_confirm tx_confirm;

	tx_confirm.packet_id = WSM_GET32(buf);
	tx_confirm.status = WSM_GET32(buf);
	tx_confirm.tx_rate = WSM_GET8(buf);
	tx_confirm.ack_failures = WSM_GET8(buf);
	tx_confirm.flags = WSM_GET16(buf);
	tx_confirm.media_delay = WSM_GET32(buf);
	tx_confirm.tx_queue_delay = WSM_GET32(buf);

	cw1200_tx_confirm_cb(priv, link_id, &tx_confirm);
	return 0;

underflow:
	WARN_ON(1);
	return -EINVAL;
}