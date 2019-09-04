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
typedef  int /*<<< orphan*/  u8 ;
struct drm_dp_link {int revision; } ;
struct drm_dp_aux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_SET_POWER ; 
 int /*<<< orphan*/  DP_SET_POWER_D0 ; 
 int /*<<< orphan*/  DP_SET_POWER_MASK ; 
 int drm_dp_dpcd_readb (struct drm_dp_aux*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_dp_dpcd_writeb (struct drm_dp_aux*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int drm_dp_link_power_up(struct drm_dp_aux *aux, struct drm_dp_link *link)
{
	u8 value;
	int err;

	/* DP_SET_POWER register is only available on DPCD v1.1 and later */
	if (link->revision < 0x11)
		return 0;

	err = drm_dp_dpcd_readb(aux, DP_SET_POWER, &value);
	if (err < 0)
		return err;

	value &= ~DP_SET_POWER_MASK;
	value |= DP_SET_POWER_D0;

	err = drm_dp_dpcd_writeb(aux, DP_SET_POWER, value);
	if (err < 0)
		return err;

	/*
	 * According to the DP 1.1 specification, a "Sink Device must exit the
	 * power saving state within 1 ms" (Section 2.5.3.1, Table 5-52, "Sink
	 * Control Field" (register 0x600).
	 */
	usleep_range(1000, 2000);

	return 0;
}