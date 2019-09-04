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
struct cpt_mbox {unsigned long long data; int /*<<< orphan*/  msg; } ;
struct cpt_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPT_MBOX_MSG_TYPE_ACK ; 
 int /*<<< orphan*/  cpt_send_msg_to_vf (struct cpt_device*,int,struct cpt_mbox*) ; 

__attribute__((used)) static void cpt_mbox_send_ack(struct cpt_device *cpt, int vf,
			      struct cpt_mbox *mbx)
{
	mbx->data = 0ull;
	mbx->msg = CPT_MBOX_MSG_TYPE_ACK;
	cpt_send_msg_to_vf(cpt, vf, mbx);
}