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
struct TYPE_2__ {int vf_valid; } ;
struct hc_sp_status_block_data {TYPE_1__ p_func; int /*<<< orphan*/  state; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 int BP_FUNC (struct bnx2x*) ; 
 scalar_t__ CSTORM_SP_STATUS_BLOCK_OFFSET (int) ; 
 int /*<<< orphan*/  CSTORM_SP_STATUS_BLOCK_SIZE ; 
 scalar_t__ CSTORM_SP_SYNC_BLOCK_OFFSET (int) ; 
 int /*<<< orphan*/  CSTORM_SP_SYNC_BLOCK_SIZE ; 
 int /*<<< orphan*/  SB_DISABLED ; 
 int /*<<< orphan*/  bnx2x_fill (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_wr_sp_sb_data (struct bnx2x*,struct hc_sp_status_block_data*) ; 
 int /*<<< orphan*/  memset (struct hc_sp_status_block_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_zero_sp_sb(struct bnx2x *bp)
{
	int func = BP_FUNC(bp);
	struct hc_sp_status_block_data sp_sb_data;
	memset(&sp_sb_data, 0, sizeof(struct hc_sp_status_block_data));

	sp_sb_data.state = SB_DISABLED;
	sp_sb_data.p_func.vf_valid = false;

	bnx2x_wr_sp_sb_data(bp, &sp_sb_data);

	bnx2x_fill(bp, BAR_CSTRORM_INTMEM +
			CSTORM_SP_STATUS_BLOCK_OFFSET(func), 0,
			CSTORM_SP_STATUS_BLOCK_SIZE);
	bnx2x_fill(bp, BAR_CSTRORM_INTMEM +
			CSTORM_SP_SYNC_BLOCK_OFFSET(func), 0,
			CSTORM_SP_SYNC_BLOCK_SIZE);
}