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
struct i40iw_sc_cqp {int /*<<< orphan*/  sq_ring; } ;

/* Variables and functions */
 int I40IW_RING_FULL_ERR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i40iw_ring_full(struct i40iw_sc_cqp *cqp)
{
	return I40IW_RING_FULL_ERR(cqp->sq_ring);
}