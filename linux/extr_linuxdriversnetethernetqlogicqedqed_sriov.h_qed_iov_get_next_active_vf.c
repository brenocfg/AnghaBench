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
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NUM_VFS ; 

__attribute__((used)) static inline u16 qed_iov_get_next_active_vf(struct qed_hwfn *p_hwfn,
					     u16 rel_vf_id)
{
	return MAX_NUM_VFS;
}