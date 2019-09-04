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
typedef  int /*<<< orphan*/  u8 ;
struct vfpf_update_tunn_param_tlv {int tun_mode_update_mask; int tunn_mode; } ;
struct qed_tunn_update_type {int b_update_mode; int b_mode_enabled; int /*<<< orphan*/  tun_cls; } ;
typedef  enum qed_tunn_mode { ____Placeholder_qed_tunn_mode } qed_tunn_mode ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static void
__qed_iov_pf_update_tun_param(struct vfpf_update_tunn_param_tlv *p_req,
			      struct qed_tunn_update_type *p_tun,
			      enum qed_tunn_mode mask, u8 tun_cls)
{
	if (p_req->tun_mode_update_mask & BIT(mask)) {
		p_tun->b_update_mode = true;

		if (p_req->tunn_mode & BIT(mask))
			p_tun->b_mode_enabled = true;
	}

	p_tun->tun_cls = tun_cls;
}