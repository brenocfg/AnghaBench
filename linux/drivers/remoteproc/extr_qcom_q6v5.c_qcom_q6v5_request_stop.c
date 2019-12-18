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
struct qcom_q6v5 {int /*<<< orphan*/  stop_bit; int /*<<< orphan*/  state; int /*<<< orphan*/  stop_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  qcom_smem_state_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

int qcom_q6v5_request_stop(struct qcom_q6v5 *q6v5)
{
	int ret;

	qcom_smem_state_update_bits(q6v5->state,
				    BIT(q6v5->stop_bit), BIT(q6v5->stop_bit));

	ret = wait_for_completion_timeout(&q6v5->stop_done, 5 * HZ);

	qcom_smem_state_update_bits(q6v5->state, BIT(q6v5->stop_bit), 0);

	return ret == 0 ? -ETIMEDOUT : 0;
}