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
struct i40iw_sc_ceq {int dummy; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int i40iw_sc_cceq_create_done (struct i40iw_sc_ceq*) ; 
 int i40iw_sc_ceq_create (struct i40iw_sc_ceq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_cceq_create(struct i40iw_sc_ceq *ceq, u64 scratch)
{
	enum i40iw_status_code ret_code;

	ret_code = i40iw_sc_ceq_create(ceq, scratch, true);
	if (!ret_code)
		ret_code = i40iw_sc_cceq_create_done(ceq);
	return ret_code;
}