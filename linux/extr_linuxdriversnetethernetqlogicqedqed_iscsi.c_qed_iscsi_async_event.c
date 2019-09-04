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
typedef  union event_ring_data {int dummy; } event_ring_data ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qed_iscsi_info {int (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union event_ring_data*) ;int /*<<< orphan*/  event_context; } ;
struct qed_hwfn {struct qed_iscsi_info* p_iscsi_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int EINVAL ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union event_ring_data*) ; 

__attribute__((used)) static int
qed_iscsi_async_event(struct qed_hwfn *p_hwfn,
		      u8 fw_event_code,
		      u16 echo, union event_ring_data *data, u8 fw_return_code)
{
	if (p_hwfn->p_iscsi_info->event_cb) {
		struct qed_iscsi_info *p_iscsi = p_hwfn->p_iscsi_info;

		return p_iscsi->event_cb(p_iscsi->event_context,
					 fw_event_code, data);
	} else {
		DP_NOTICE(p_hwfn, "iSCSI async completion is not set\n");
		return -EINVAL;
	}
}