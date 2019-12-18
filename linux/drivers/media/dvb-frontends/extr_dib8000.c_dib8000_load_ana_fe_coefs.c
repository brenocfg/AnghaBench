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
struct dib8000_state {scalar_t__ isdbt_cfg_loaded; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void dib8000_load_ana_fe_coefs(struct dib8000_state *state, const s16 *ana_fe)
{
	u16 mode = 0;

	if (state->isdbt_cfg_loaded == 0)
		for (mode = 0; mode < 24; mode++)
			dib8000_write_word(state, 117 + mode, ana_fe[mode]);
}