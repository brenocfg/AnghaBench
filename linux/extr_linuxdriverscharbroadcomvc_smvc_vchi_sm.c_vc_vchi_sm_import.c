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
struct vc_sm_import_result {int dummy; } ;
struct vc_sm_import {int dummy; } ;
struct sm_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_SM_MSG_TYPE_IMPORT ; 
 int vc_vchi_sm_send_msg (struct sm_instance*,int /*<<< orphan*/ ,struct vc_sm_import*,int,struct vc_sm_import_result*,int,int /*<<< orphan*/ *,int) ; 

int vc_vchi_sm_import(struct sm_instance *handle, struct vc_sm_import *msg,
		      struct vc_sm_import_result *result,
		      uint32_t *cur_trans_id)
{
	return vc_vchi_sm_send_msg(handle, VC_SM_MSG_TYPE_IMPORT,
				   msg, sizeof(*msg), result, sizeof(*result),
				   cur_trans_id, 1);
}