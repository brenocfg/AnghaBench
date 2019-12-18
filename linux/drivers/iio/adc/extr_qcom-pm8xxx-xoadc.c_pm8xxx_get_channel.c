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
typedef  scalar_t__ u8 ;
struct pm8xxx_xoadc {int nchans; struct pm8xxx_chan_info* chans; } ;
struct pm8xxx_chan_info {TYPE_1__* hwchan; } ;
struct TYPE_2__ {scalar_t__ amux_channel; } ;

/* Variables and functions */

__attribute__((used)) static struct pm8xxx_chan_info *
pm8xxx_get_channel(struct pm8xxx_xoadc *adc, u8 chan)
{
	int i;

	for (i = 0; i < adc->nchans; i++) {
		struct pm8xxx_chan_info *ch = &adc->chans[i];
		if (ch->hwchan->amux_channel == chan)
			return ch;
	}
	return NULL;
}