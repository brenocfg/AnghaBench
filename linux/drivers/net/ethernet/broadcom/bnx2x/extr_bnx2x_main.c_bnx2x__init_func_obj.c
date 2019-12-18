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
struct bnx2x {int /*<<< orphan*/  func_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_func_sp_drv ; 
 int /*<<< orphan*/  bnx2x_init_func_obj (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_setup_dmae (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_sp (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_sp_mapping (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_afex_rdata ; 
 int /*<<< orphan*/  func_rdata ; 

void bnx2x__init_func_obj(struct bnx2x *bp)
{
	/* Prepare DMAE related driver resources */
	bnx2x_setup_dmae(bp);

	bnx2x_init_func_obj(bp, &bp->func_obj,
			    bnx2x_sp(bp, func_rdata),
			    bnx2x_sp_mapping(bp, func_rdata),
			    bnx2x_sp(bp, func_afex_rdata),
			    bnx2x_sp_mapping(bp, func_afex_rdata),
			    &bnx2x_func_sp_drv);
}