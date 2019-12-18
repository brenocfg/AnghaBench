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
struct i40e_vf {int dummy; } ;
typedef  int /*<<< orphan*/  i40e_status ;
typedef  enum virtchnl_ops { ____Placeholder_virtchnl_ops } virtchnl_ops ;

/* Variables and functions */
 int i40e_vc_send_msg_to_vf (struct i40e_vf*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_vc_send_resp_to_vf(struct i40e_vf *vf,
				   enum virtchnl_ops opcode,
				   i40e_status retval)
{
	return i40e_vc_send_msg_to_vf(vf, opcode, retval, NULL, 0);
}