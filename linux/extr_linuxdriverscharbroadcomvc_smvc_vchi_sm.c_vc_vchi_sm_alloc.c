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
typedef  int /*<<< orphan*/  uint32_t ;
struct vc_sm_alloc_t {int dummy; } ;
struct vc_sm_alloc_result_t {int dummy; } ;
struct sm_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_SM_MSG_TYPE_ALLOC ; 
 int vc_vchi_sm_send_msg (struct sm_instance*,int /*<<< orphan*/ ,struct vc_sm_alloc_t*,int,struct vc_sm_alloc_result_t*,int,int /*<<< orphan*/ *,int) ; 

int vc_vchi_sm_alloc(struct sm_instance *handle, struct vc_sm_alloc_t *msg,
		     struct vc_sm_alloc_result_t *result,
		     uint32_t *cur_trans_id)
{
	return vc_vchi_sm_send_msg(handle, VC_SM_MSG_TYPE_ALLOC,
				   msg, sizeof(*msg), result, sizeof(*result),
				   cur_trans_id, 1);
}