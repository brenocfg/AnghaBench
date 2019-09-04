#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct s5c73m3_ctrls {TYPE_4__* af_stop; TYPE_3__* focus_auto; TYPE_2__* af_start; TYPE_1__* af_distance; } ;
struct s5c73m3 {struct s5c73m3_ctrls ctrls; } ;
struct TYPE_8__ {scalar_t__ is_new; } ;
struct TYPE_7__ {scalar_t__ val; scalar_t__ is_new; } ;
struct TYPE_6__ {scalar_t__ is_new; } ;
struct TYPE_5__ {scalar_t__ val; scalar_t__ is_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_AF_MODE ; 
 int /*<<< orphan*/  COMM_AF_MODE_MACRO ; 
 int /*<<< orphan*/  COMM_AF_MODE_NORMAL ; 
 scalar_t__ V4L2_AUTO_FOCUS_RANGE_MACRO ; 
 int s5c73m3_af_run (struct s5c73m3*,int) ; 
 int s5c73m3_isp_command (struct s5c73m3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5c73m3_set_auto_focus(struct s5c73m3 *state, int caf)
{
	struct s5c73m3_ctrls *c = &state->ctrls;
	int ret = 1;

	if (c->af_distance->is_new) {
		u16 mode = (c->af_distance->val == V4L2_AUTO_FOCUS_RANGE_MACRO)
				? COMM_AF_MODE_MACRO : COMM_AF_MODE_NORMAL;
		ret = s5c73m3_isp_command(state, COMM_AF_MODE, mode);
		if (ret != 0)
			return ret;
	}

	if (!ret || (c->focus_auto->is_new && c->focus_auto->val) ||
							c->af_start->is_new)
		ret = s5c73m3_af_run(state, 1);
	else if ((c->focus_auto->is_new && !c->focus_auto->val) ||
							c->af_stop->is_new)
		ret = s5c73m3_af_run(state, 0);
	else
		ret = 0;

	return ret;
}