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
struct qed_load_req_params {int /*<<< orphan*/  override_force_load; int /*<<< orphan*/  avoid_eng_reset; int /*<<< orphan*/  timeout_val; int /*<<< orphan*/  drv_role; } ;
struct qed_drv_load_params {int /*<<< orphan*/  override_force_load; int /*<<< orphan*/  avoid_eng_reset; int /*<<< orphan*/  mfw_timeout_val; scalar_t__ is_crash_kernel; } ;

/* Variables and functions */
 int /*<<< orphan*/  QED_DRV_ROLE_KDUMP ; 
 int /*<<< orphan*/  QED_DRV_ROLE_OS ; 
 int /*<<< orphan*/  memset (struct qed_load_req_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qed_fill_load_req_params(struct qed_load_req_params *p_load_req,
			 struct qed_drv_load_params *p_drv_load)
{
	memset(p_load_req, 0, sizeof(*p_load_req));

	p_load_req->drv_role = p_drv_load->is_crash_kernel ?
			       QED_DRV_ROLE_KDUMP : QED_DRV_ROLE_OS;
	p_load_req->timeout_val = p_drv_load->mfw_timeout_val;
	p_load_req->avoid_eng_reset = p_drv_load->avoid_eng_reset;
	p_load_req->override_force_load = p_drv_load->override_force_load;
}