#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_4__ {TYPE_1__* vflip; } ;
struct s5k5baf {scalar_t__ streaming; TYPE_2__ ctrls; } ;
struct TYPE_3__ {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_P_PREV_MIRROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_hw_sync_cfg (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_write (struct s5k5baf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s5k5baf_hw_set_mirror(struct s5k5baf *state)
{
	u16 flip = state->ctrls.vflip->val | (state->ctrls.vflip->val << 1);

	s5k5baf_write(state, REG_P_PREV_MIRROR(0), flip);
	if (state->streaming)
		s5k5baf_hw_sync_cfg(state);
}