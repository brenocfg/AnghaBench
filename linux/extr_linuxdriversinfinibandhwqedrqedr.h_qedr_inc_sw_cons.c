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
struct qedr_qp_hwq_info {int cons; int max_wr; int /*<<< orphan*/  wqe_cons; } ;

/* Variables and functions */

__attribute__((used)) static inline void qedr_inc_sw_cons(struct qedr_qp_hwq_info *info)
{
	info->cons = (info->cons + 1) % info->max_wr;
	info->wqe_cons++;
}