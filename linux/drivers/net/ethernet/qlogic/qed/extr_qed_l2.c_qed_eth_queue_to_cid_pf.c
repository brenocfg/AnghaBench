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
typedef  int /*<<< orphan*/  u16 ;
struct qed_queue_start_common_params {int dummy; } ;
struct qed_queue_cid {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 struct qed_queue_cid* qed_eth_queue_to_cid (struct qed_hwfn*,int /*<<< orphan*/ ,struct qed_queue_start_common_params*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct qed_queue_cid *
qed_eth_queue_to_cid_pf(struct qed_hwfn *p_hwfn,
			u16 opaque_fid,
			bool b_is_rx,
			struct qed_queue_start_common_params *p_params)
{
	return qed_eth_queue_to_cid(p_hwfn, opaque_fid, p_params, b_is_rx,
				    NULL);
}