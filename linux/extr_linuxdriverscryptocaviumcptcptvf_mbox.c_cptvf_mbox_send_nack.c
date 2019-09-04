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
struct cpt_vf {int dummy; } ;
struct cpt_mbox {int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPT_MBOX_MSG_TYPE_NACK ; 
 int /*<<< orphan*/  cptvf_send_msg_to_pf (struct cpt_vf*,struct cpt_mbox*) ; 

void cptvf_mbox_send_nack(struct cpt_vf *cptvf, struct cpt_mbox *mbx)
{
	mbx->msg = CPT_MBOX_MSG_TYPE_NACK;
	cptvf_send_msg_to_pf(cptvf, mbx);
}