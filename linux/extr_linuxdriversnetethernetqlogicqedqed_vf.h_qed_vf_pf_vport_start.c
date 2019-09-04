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
typedef  int /*<<< orphan*/  u16 ;
struct qed_hwfn {int dummy; } ;
typedef  enum qed_tpa_mode { ____Placeholder_qed_tpa_mode } qed_tpa_mode ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int qed_vf_pf_vport_start(struct qed_hwfn *p_hwfn,
					u8 vport_id,
					u16 mtu,
					u8 inner_vlan_removal,
					enum qed_tpa_mode tpa_mode,
					u8 max_buffers_per_cqe,
					u8 only_untagged)
{
	return -EINVAL;
}