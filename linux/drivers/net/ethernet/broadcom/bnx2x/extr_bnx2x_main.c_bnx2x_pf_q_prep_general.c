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
typedef  int /*<<< orphan*/  u8 ;
struct bnx2x_general_setup_params {int /*<<< orphan*/  fp_hsi; int /*<<< orphan*/  cos; int /*<<< orphan*/  mtu; int /*<<< orphan*/  spcl_id; int /*<<< orphan*/  stat_id; } ;
struct bnx2x_fastpath {int /*<<< orphan*/  cl_id; } ;
struct bnx2x {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FCOE_MINI_JUMBO_MTU ; 
 int /*<<< orphan*/  ETH_FP_HSI_VERSION ; 
 scalar_t__ IS_FCOE_FP (struct bnx2x_fastpath*) ; 
 int /*<<< orphan*/  bnx2x_stats_id (struct bnx2x_fastpath*) ; 

__attribute__((used)) static void bnx2x_pf_q_prep_general(struct bnx2x *bp,
	struct bnx2x_fastpath *fp, struct bnx2x_general_setup_params *gen_init,
	u8 cos)
{
	gen_init->stat_id = bnx2x_stats_id(fp);
	gen_init->spcl_id = fp->cl_id;

	/* Always use mini-jumbo MTU for FCoE L2 ring */
	if (IS_FCOE_FP(fp))
		gen_init->mtu = BNX2X_FCOE_MINI_JUMBO_MTU;
	else
		gen_init->mtu = bp->dev->mtu;

	gen_init->cos = cos;

	gen_init->fp_hsi = ETH_FP_HSI_VERSION;
}