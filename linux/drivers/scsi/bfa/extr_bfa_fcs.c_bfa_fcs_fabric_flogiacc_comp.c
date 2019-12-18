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
typedef  int /*<<< orphan*/  u32 ;
struct fchs_s {int dummy; } ;
struct bfa_fcxp_s {int dummy; } ;
struct bfa_fcs_fabric_s {int /*<<< orphan*/  fcs; } ;
typedef  int /*<<< orphan*/  bfa_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_fabric_flogiacc_comp(void *fcsarg, struct bfa_fcxp_s *fcxp, void *cbarg,
			     bfa_status_t status, u32 rsp_len,
			     u32 resid_len, struct fchs_s *rspfchs)
{
	struct bfa_fcs_fabric_s *fabric = cbarg;

	bfa_trc(fabric->fcs, status);
}