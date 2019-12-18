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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct link_params {scalar_t__ port; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIG_REG_P0_MAC_IN_EN ; 
 int /*<<< orphan*/  NIG_REG_P0_MAC_OUT_EN ; 
 int /*<<< orphan*/  NIG_REG_P0_MAC_PAUSE_OUT_EN ; 
 int /*<<< orphan*/  NIG_REG_P1_MAC_IN_EN ; 
 int /*<<< orphan*/  NIG_REG_P1_MAC_OUT_EN ; 
 int /*<<< orphan*/  NIG_REG_P1_MAC_PAUSE_OUT_EN ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_set_xumac_nig(struct link_params *params,
				u16 tx_pause_en,
				u8 enable)
{
	struct bnx2x *bp = params->bp;

	REG_WR(bp, params->port ? NIG_REG_P1_MAC_IN_EN : NIG_REG_P0_MAC_IN_EN,
	       enable);
	REG_WR(bp, params->port ? NIG_REG_P1_MAC_OUT_EN : NIG_REG_P0_MAC_OUT_EN,
	       enable);
	REG_WR(bp, params->port ? NIG_REG_P1_MAC_PAUSE_OUT_EN :
	       NIG_REG_P0_MAC_PAUSE_OUT_EN, tx_pause_en);
}