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
typedef  size_t u32 ;
struct asc_board {int /*<<< orphan*/ * adv_reqp; } ;
struct adv_dvc_var {size_t max_host_qng; struct asc_board* drv_ptr; } ;
typedef  int /*<<< orphan*/  adv_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static adv_req_t * adv_get_reqp(struct adv_dvc_var *adv_dvc, u32 offset)
{
	struct asc_board *boardp = adv_dvc->drv_ptr;

	BUG_ON(offset > adv_dvc->max_host_qng);
	return &boardp->adv_reqp[offset];
}