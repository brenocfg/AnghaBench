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
typedef  scalar_t__ u8 ;
struct qed_vf_info {scalar_t__ num_rxqs; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QED_IOV_VALIDATE_Q_ENABLE ; 
 scalar_t__ qed_iov_validate_queue_mode (struct qed_hwfn*,struct qed_vf_info*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool qed_iov_validate_active_rxq(struct qed_hwfn *p_hwfn,
					struct qed_vf_info *p_vf)
{
	u8 i;

	for (i = 0; i < p_vf->num_rxqs; i++)
		if (qed_iov_validate_queue_mode(p_hwfn, p_vf, i,
						QED_IOV_VALIDATE_Q_ENABLE,
						false))
			return true;

	return false;
}