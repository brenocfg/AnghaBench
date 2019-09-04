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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  x_pos; } ;
struct at91_adc_state {TYPE_1__ touch_st; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SAMA5D2_XPOSR ; 
 int /*<<< orphan*/  at91_adc_touch_pos (struct at91_adc_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 at91_adc_touch_x_pos(struct at91_adc_state *st)
{
	st->touch_st.x_pos = at91_adc_touch_pos(st, AT91_SAMA5D2_XPOSR);
	return st->touch_st.x_pos;
}