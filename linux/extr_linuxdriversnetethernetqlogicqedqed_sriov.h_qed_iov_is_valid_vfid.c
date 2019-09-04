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
struct qed_hwfn {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
qed_iov_is_valid_vfid(struct qed_hwfn *p_hwfn,
		      int rel_vf_id, bool b_enabled_only, bool b_non_malicious)
{
	return false;
}