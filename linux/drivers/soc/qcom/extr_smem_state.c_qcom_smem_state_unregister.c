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
struct qcom_smem_state {int orphan; } ;

/* Variables and functions */
 int /*<<< orphan*/  qcom_smem_state_put (struct qcom_smem_state*) ; 

void qcom_smem_state_unregister(struct qcom_smem_state *state)
{
	state->orphan = true;
	qcom_smem_state_put(state);
}