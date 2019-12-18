#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct display_mode_lib {int dummy; } ;
typedef  int /*<<< orphan*/  display_rq_regs_st ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ display_rq_params_st ;
struct TYPE_7__ {int /*<<< orphan*/  src; } ;
typedef  TYPE_2__ display_pipe_params_st ;

/* Variables and functions */
 int /*<<< orphan*/  dml20_rq_dlg_get_rq_params (struct display_mode_lib*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_rq_regs (struct display_mode_lib*,int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print__rq_regs_st (struct display_mode_lib*,int /*<<< orphan*/ ) ; 

void dml20_rq_dlg_get_rq_reg(struct display_mode_lib *mode_lib,
		display_rq_regs_st *rq_regs,
		const display_pipe_params_st pipe_param)
{
	display_rq_params_st rq_param = {0};

	memset(rq_regs, 0, sizeof(*rq_regs));
	dml20_rq_dlg_get_rq_params(mode_lib, &rq_param, pipe_param.src);
	extract_rq_regs(mode_lib, rq_regs, rq_param);

	print__rq_regs_st(mode_lib, *rq_regs);
}