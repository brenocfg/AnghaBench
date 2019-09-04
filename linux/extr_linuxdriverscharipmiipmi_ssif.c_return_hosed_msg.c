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
struct ssif_info {int dummy; } ;
struct ipmi_smi_msg {int* rsp; int* data; int rsp_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  deliver_recv_msg (struct ssif_info*,struct ipmi_smi_msg*) ; 
 int /*<<< orphan*/  hosed ; 
 int /*<<< orphan*/  ssif_inc_stat (struct ssif_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void return_hosed_msg(struct ssif_info *ssif_info,
			     struct ipmi_smi_msg *msg)
{
	ssif_inc_stat(ssif_info, hosed);

	/* Make it a response */
	msg->rsp[0] = msg->data[0] | 4;
	msg->rsp[1] = msg->data[1];
	msg->rsp[2] = 0xFF; /* Unknown error. */
	msg->rsp_size = 3;

	deliver_recv_msg(ssif_info, msg);
}