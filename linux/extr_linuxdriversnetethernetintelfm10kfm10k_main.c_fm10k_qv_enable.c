#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int itr; } ;
struct fm10k_q_vector {int /*<<< orphan*/  itr; TYPE_1__ rx; TYPE_1__ tx; } ;

/* Variables and functions */
 int FM10K_ITR_ENABLE ; 
 int FM10K_ITR_INTERVAL1_SHIFT ; 
 int FM10K_ITR_MAX ; 
 int /*<<< orphan*/  fm10k_update_itr (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_qv_enable(struct fm10k_q_vector *q_vector)
{
	/* Enable auto-mask and clear the current mask */
	u32 itr = FM10K_ITR_ENABLE;

	/* Update Tx ITR */
	fm10k_update_itr(&q_vector->tx);

	/* Update Rx ITR */
	fm10k_update_itr(&q_vector->rx);

	/* Store Tx itr in timer slot 0 */
	itr |= (q_vector->tx.itr & FM10K_ITR_MAX);

	/* Shift Rx itr to timer slot 1 */
	itr |= (q_vector->rx.itr & FM10K_ITR_MAX) << FM10K_ITR_INTERVAL1_SHIFT;

	/* Write the final value to the ITR register */
	writel(itr, q_vector->itr);
}