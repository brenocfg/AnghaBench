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
struct qed_hwfn {int b_int_enabled; } ;
struct qed_hw_init_params {scalar_t__ p_tunn; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_vf_pf_tunnel_param_update (struct qed_hwfn*,scalar_t__) ; 
 int /*<<< orphan*/  qed_vf_set_vf_start_tunn_update_param (scalar_t__) ; 

__attribute__((used)) static int qed_vf_start(struct qed_hwfn *p_hwfn,
			struct qed_hw_init_params *p_params)
{
	if (p_params->p_tunn) {
		qed_vf_set_vf_start_tunn_update_param(p_params->p_tunn);
		qed_vf_pf_tunnel_param_update(p_hwfn, p_params->p_tunn);
	}

	p_hwfn->b_int_enabled = true;

	return 0;
}