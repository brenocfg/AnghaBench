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
struct i40iw_cqp_request {int /*<<< orphan*/  refcount; } ;
struct i40iw_cqp {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_free_cqp_request (struct i40iw_cqp*,struct i40iw_cqp_request*) ; 

void i40iw_put_cqp_request(struct i40iw_cqp *cqp,
			   struct i40iw_cqp_request *cqp_request)
{
	if (atomic_dec_and_test(&cqp_request->refcount))
		i40iw_free_cqp_request(cqp, cqp_request);
}