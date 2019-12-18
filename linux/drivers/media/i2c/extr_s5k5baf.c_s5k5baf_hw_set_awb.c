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
struct s5k5baf_ctrls {TYPE_2__* gain_blue; TYPE_1__* gain_red; } ;
struct s5k5baf {struct s5k5baf_ctrls ctrls; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  AALG_WB_EN ; 
 int /*<<< orphan*/  REG_SF_RGAIN ; 
 int /*<<< orphan*/  S5K5BAF_GAIN_GREEN_DEF ; 
 int /*<<< orphan*/  s5k5baf_hw_set_alg (struct s5k5baf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s5k5baf_write_seq (struct s5k5baf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void s5k5baf_hw_set_awb(struct s5k5baf *state, int awb)
{
	struct s5k5baf_ctrls *ctrls = &state->ctrls;

	if (!awb)
		s5k5baf_write_seq(state, REG_SF_RGAIN,
				  ctrls->gain_red->val, 1,
				  S5K5BAF_GAIN_GREEN_DEF, 1,
				  ctrls->gain_blue->val, 1,
				  1);

	s5k5baf_hw_set_alg(state, AALG_WB_EN, awb);
}