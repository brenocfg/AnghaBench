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
struct s5k5baf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AALG_FLICKER_EN ; 
 int /*<<< orphan*/  REG_SF_FLICKER_QUANT ; 
 int V4L2_CID_POWER_LINE_FREQUENCY_AUTO ; 
 int /*<<< orphan*/  s5k5baf_hw_set_alg (struct s5k5baf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s5k5baf_write_seq (struct s5k5baf*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void s5k5baf_hw_set_anti_flicker(struct s5k5baf *state, int v)
{
	if (v == V4L2_CID_POWER_LINE_FREQUENCY_AUTO) {
		s5k5baf_hw_set_alg(state, AALG_FLICKER_EN, true);
	} else {
		/* The V4L2_CID_LINE_FREQUENCY control values match
		 * the register values */
		s5k5baf_write_seq(state, REG_SF_FLICKER_QUANT, v, 1);
		s5k5baf_hw_set_alg(state, AALG_FLICKER_EN, false);
	}
}