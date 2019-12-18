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
typedef  int /*<<< orphan*/  u16 ;
struct pm8xxx_xoadc {int dummy; } ;
struct pm8xxx_chan_info {int dummy; } ;

/* Variables and functions */
 int pm8xxx_read_channel_rsv (struct pm8xxx_xoadc*,struct pm8xxx_chan_info const*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pm8xxx_read_channel(struct pm8xxx_xoadc *adc,
			       const struct pm8xxx_chan_info *ch,
			       u16 *adc_code)
{
	/*
	 * Normally we just use the ratiometric scale value (RSV) predefined
	 * for the channel, but during calibration we need to modify this
	 * so this wrapper is a helper hiding the more complex version.
	 */
	return pm8xxx_read_channel_rsv(adc, ch, 0xff, adc_code, false);
}