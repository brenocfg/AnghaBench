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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ in_soc; } ;
struct dib0090_state {TYPE_1__ identity; } ;

/* Variables and functions */
 int dib0090_read_reg (struct dib0090_state*,int) ; 

__attribute__((used)) static u32 dib0090_get_slow_adc_val(struct dib0090_state *state)
{
	u16 adc_val = dib0090_read_reg(state, 0x1d);
	if (state->identity.in_soc)
		adc_val >>= 2;
	return adc_val;
}