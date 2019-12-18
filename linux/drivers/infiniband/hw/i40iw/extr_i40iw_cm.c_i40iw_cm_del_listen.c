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
struct i40iw_cm_listener {int /*<<< orphan*/ * cm_id; int /*<<< orphan*/  listener_state; } ;
struct i40iw_cm_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CM_LISTENER_PASSIVE_STATE ; 
 int i40iw_dec_refcnt_listen (struct i40iw_cm_core*,struct i40iw_cm_listener*,int,int) ; 

__attribute__((used)) static int i40iw_cm_del_listen(struct i40iw_cm_core *cm_core,
			       struct i40iw_cm_listener *listener,
			       bool apbvt_del)
{
	listener->listener_state = I40IW_CM_LISTENER_PASSIVE_STATE;
	listener->cm_id = NULL;	/* going to be destroyed pretty soon */
	return i40iw_dec_refcnt_listen(cm_core, listener, 1, apbvt_del);
}