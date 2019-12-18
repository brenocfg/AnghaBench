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
typedef  enum qed_iov_wq_flag { ____Placeholder_qed_iov_wq_flag } qed_iov_wq_flag ;

/* Variables and functions */

__attribute__((used)) static inline void qed_schedule_iov(struct qed_hwfn *hwfn,
				    enum qed_iov_wq_flag flag)
{
}