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
struct vc_sm_action_clean_t {int dummy; } ;
struct sm_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_SM_MSG_TYPE_ACTION_CLEAN ; 
 int vc_vchi_sm_send_msg (struct sm_instance*,int /*<<< orphan*/ ,struct vc_sm_action_clean_t*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vc_vchi_sm_clean_up(struct sm_instance *handle,
			struct vc_sm_action_clean_t *msg)
{
	return vc_vchi_sm_send_msg(handle, VC_SM_MSG_TYPE_ACTION_CLEAN,
				   msg, sizeof(*msg), 0, 0, 0, 0);
}