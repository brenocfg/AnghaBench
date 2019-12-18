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
struct gsm_mux {int /*<<< orphan*/ * dlci; int /*<<< orphan*/  ftype; } ;
struct gsm_msg {int* data; } ;
struct gsm_control {int cmd; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EA ; 
 struct gsm_msg* gsm_data_alloc (struct gsm_mux*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsm_data_queue (int /*<<< orphan*/ ,struct gsm_msg*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gsm_control_transmit(struct gsm_mux *gsm, struct gsm_control *ctrl)
{
	struct gsm_msg *msg = gsm_data_alloc(gsm, 0, ctrl->len + 1, gsm->ftype);
	if (msg == NULL)
		return;
	msg->data[0] = (ctrl->cmd << 1) | 2 | EA;	/* command */
	memcpy(msg->data + 1, ctrl->data, ctrl->len);
	gsm_data_queue(gsm->dlci[0], msg);
}