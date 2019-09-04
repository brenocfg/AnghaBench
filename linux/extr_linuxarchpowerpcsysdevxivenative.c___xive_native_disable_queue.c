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
typedef  int /*<<< orphan*/  u32 ;
struct xive_q {int dummy; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ OPAL_BUSY ; 
 int /*<<< orphan*/  OPAL_BUSY_DELAY_MS ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_xive_set_queue_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __xive_native_disable_queue(u32 vp_id, struct xive_q *q, u8 prio)
{
	s64 rc;

	/* Disable the queue in HW */
	for (;;) {
		rc = opal_xive_set_queue_info(vp_id, prio, 0, 0, 0);
		if (rc != OPAL_BUSY)
			break;
		msleep(OPAL_BUSY_DELAY_MS);
	}
	if (rc)
		pr_err("Error %lld disabling queue for prio %d\n", rc, prio);
}