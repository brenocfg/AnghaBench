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
struct qed_spq_comp_done {int /*<<< orphan*/  done; int /*<<< orphan*/  fw_return_code; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void qed_spq_blocking_cb(struct qed_hwfn *p_hwfn,
				void *cookie,
				union event_ring_data *data, u8 fw_return_code)
{
	struct qed_spq_comp_done *comp_done;

	comp_done = (struct qed_spq_comp_done *)cookie;

	comp_done->fw_return_code = fw_return_code;

	/* Make sure completion done is visible on waiting thread */
	smp_store_release(&comp_done->done, 0x1);
}