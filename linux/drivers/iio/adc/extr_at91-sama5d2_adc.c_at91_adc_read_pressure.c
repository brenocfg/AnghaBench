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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  touching; } ;
struct at91_adc_state {TYPE_1__ touch_st; } ;

/* Variables and functions */
 int AT91_SAMA5D2_TOUCH_P_CHAN_IDX ; 
 int ENODATA ; 
 int IIO_VAL_INT ; 
 scalar_t__ at91_adc_touch_pressure (struct at91_adc_state*) ; 

__attribute__((used)) static int at91_adc_read_pressure(struct at91_adc_state *st, int chan, u16 *val)
{
	*val = 0;
	if (!st->touch_st.touching)
		return -ENODATA;
	if (chan == AT91_SAMA5D2_TOUCH_P_CHAN_IDX)
		*val = at91_adc_touch_pressure(st);
	else
		return -ENODATA;

	return IIO_VAL_INT;
}