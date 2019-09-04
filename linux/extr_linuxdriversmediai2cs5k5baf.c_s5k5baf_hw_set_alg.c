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
typedef  int u16 ;
struct s5k5baf {int valid_auto_alg; int auto_alg; scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_DBG_AUTOALG_EN ; 
 int s5k5baf_read (struct s5k5baf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_write (struct s5k5baf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s5k5baf_hw_set_alg(struct s5k5baf *state, u16 alg, bool enable)
{
	u16 cur_alg, new_alg;

	if (!state->valid_auto_alg)
		cur_alg = s5k5baf_read(state, REG_DBG_AUTOALG_EN);
	else
		cur_alg = state->auto_alg;

	new_alg = enable ? (cur_alg | alg) : (cur_alg & ~alg);

	if (new_alg != cur_alg)
		s5k5baf_write(state, REG_DBG_AUTOALG_EN, new_alg);

	if (state->error)
		return;

	state->valid_auto_alg = 1;
	state->auto_alg = new_alg;
}