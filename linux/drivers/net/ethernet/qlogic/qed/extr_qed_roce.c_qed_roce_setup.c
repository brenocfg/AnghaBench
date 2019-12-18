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
 int /*<<< orphan*/  PROTOCOLID_ROCE ; 
 int /*<<< orphan*/  qed_roce_async_event ; 
 int qed_spq_register_async_cb (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qed_roce_setup(struct qed_hwfn *p_hwfn)
{
	return qed_spq_register_async_cb(p_hwfn, PROTOCOLID_ROCE,
					 qed_roce_async_event);
}