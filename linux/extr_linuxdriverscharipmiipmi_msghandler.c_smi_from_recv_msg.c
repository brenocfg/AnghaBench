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
struct ipmi_smi_msg {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; int /*<<< orphan*/  msgid; } ;
struct ipmi_smi {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; } ;
struct ipmi_recv_msg {TYPE_1__ msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  STORE_SEQ_IN_MSGID (unsigned char,long) ; 
 struct ipmi_smi_msg* ipmi_alloc_smi_msg () ; 
 int /*<<< orphan*/  ipmi_debug_msg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ipmi_smi_msg *
smi_from_recv_msg(struct ipmi_smi *intf, struct ipmi_recv_msg *recv_msg,
		  unsigned char seq, long seqid)
{
	struct ipmi_smi_msg *smi_msg = ipmi_alloc_smi_msg();
	if (!smi_msg)
		/*
		 * If we can't allocate the message, then just return, we
		 * get 4 retries, so this should be ok.
		 */
		return NULL;

	memcpy(smi_msg->data, recv_msg->msg.data, recv_msg->msg.data_len);
	smi_msg->data_size = recv_msg->msg.data_len;
	smi_msg->msgid = STORE_SEQ_IN_MSGID(seq, seqid);

	ipmi_debug_msg("Resend: ", smi_msg->data, smi_msg->data_size);

	return smi_msg;
}