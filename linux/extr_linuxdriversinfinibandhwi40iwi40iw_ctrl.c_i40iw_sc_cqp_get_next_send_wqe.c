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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct i40iw_sc_cqp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * i40iw_sc_cqp_get_next_send_wqe_idx (struct i40iw_sc_cqp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u64 *i40iw_sc_cqp_get_next_send_wqe(struct i40iw_sc_cqp *cqp, u64 scratch)
{
	u32 wqe_idx;

	return i40iw_sc_cqp_get_next_send_wqe_idx(cqp, scratch, &wqe_idx);
}