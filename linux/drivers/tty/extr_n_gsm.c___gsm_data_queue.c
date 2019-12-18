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
typedef  int u8 ;
struct gsm_mux {scalar_t__ encoding; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_list; scalar_t__ initiator; } ;
struct gsm_msg {int* data; int len; int ctrl; int addr; int /*<<< orphan*/  list; } ;
struct gsm_dlci {struct gsm_mux* gsm; } ;

/* Variables and functions */
 int EA ; 
 int INIT_FCS ; 
 int PF ; 
 int UI ; 
 int /*<<< orphan*/  gsm_data_kick (struct gsm_mux*) ; 
 int gsm_fcs_add_block (int,int*,int) ; 
 int /*<<< orphan*/  gsm_print_packet (char*,int,scalar_t__,int,int*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __gsm_data_queue(struct gsm_dlci *dlci, struct gsm_msg *msg)
{
	struct gsm_mux *gsm = dlci->gsm;
	u8 *dp = msg->data;
	u8 *fcs = dp + msg->len;

	/* Fill in the header */
	if (gsm->encoding == 0) {
		if (msg->len < 128)
			*--dp = (msg->len << 1) | EA;
		else {
			*--dp = (msg->len >> 7);	/* bits 7 - 15 */
			*--dp = (msg->len & 127) << 1;	/* bits 0 - 6 */
		}
	}

	*--dp = msg->ctrl;
	if (gsm->initiator)
		*--dp = (msg->addr << 2) | 2 | EA;
	else
		*--dp = (msg->addr << 2) | EA;
	*fcs = gsm_fcs_add_block(INIT_FCS, dp , msg->data - dp);
	/* Ugly protocol layering violation */
	if (msg->ctrl == UI || msg->ctrl == (UI|PF))
		*fcs = gsm_fcs_add_block(*fcs, msg->data, msg->len);
	*fcs = 0xFF - *fcs;

	gsm_print_packet("Q> ", msg->addr, gsm->initiator, msg->ctrl,
							msg->data, msg->len);

	/* Move the header back and adjust the length, also allow for the FCS
	   now tacked on the end */
	msg->len += (msg->data - dp) + 1;
	msg->data = dp;

	/* Add to the actual output queue */
	list_add_tail(&msg->list, &gsm->tx_list);
	gsm->tx_bytes += msg->len;
	gsm_data_kick(gsm);
}