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
typedef  int u32 ;
struct csis_state {int num_lanes; scalar_t__ wclk_ext; TYPE_1__* csis_fmt; int /*<<< orphan*/  hs_settle; } ;
struct TYPE_2__ {int data_alignment; } ;

/* Variables and functions */
 int S5PCSIS_CFG_NR_LANE_MASK ; 
 int /*<<< orphan*/  S5PCSIS_CONFIG ; 
 int /*<<< orphan*/  S5PCSIS_CTRL ; 
 int S5PCSIS_CTRL_ALIGN_32BIT ; 
 int S5PCSIS_CTRL_UPDATE_SHADOW ; 
 int S5PCSIS_CTRL_WCLK_EXTCLK ; 
 int /*<<< orphan*/  __s5pcsis_set_format (struct csis_state*) ; 
 int s5pcsis_read (struct csis_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5pcsis_set_hsync_settle (struct csis_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5pcsis_write (struct csis_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s5pcsis_set_params(struct csis_state *state)
{
	u32 val;

	val = s5pcsis_read(state, S5PCSIS_CONFIG);
	val = (val & ~S5PCSIS_CFG_NR_LANE_MASK) | (state->num_lanes - 1);
	s5pcsis_write(state, S5PCSIS_CONFIG, val);

	__s5pcsis_set_format(state);
	s5pcsis_set_hsync_settle(state, state->hs_settle);

	val = s5pcsis_read(state, S5PCSIS_CTRL);
	if (state->csis_fmt->data_alignment == 32)
		val |= S5PCSIS_CTRL_ALIGN_32BIT;
	else /* 24-bits */
		val &= ~S5PCSIS_CTRL_ALIGN_32BIT;

	val &= ~S5PCSIS_CTRL_WCLK_EXTCLK;
	if (state->wclk_ext)
		val |= S5PCSIS_CTRL_WCLK_EXTCLK;
	s5pcsis_write(state, S5PCSIS_CTRL, val);

	/* Update the shadow register. */
	val = s5pcsis_read(state, S5PCSIS_CTRL);
	s5pcsis_write(state, S5PCSIS_CTRL, val | S5PCSIS_CTRL_UPDATE_SHADOW);
}