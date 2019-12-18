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
struct ti_bandgap {TYPE_1__* conf; } ;
struct TYPE_2__ {int sensor_count; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  POWER_SWITCH ; 
 int /*<<< orphan*/  RMW_BITS (struct ti_bandgap*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TI_BANDGAP_HAS (struct ti_bandgap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgap_tempsoff_mask ; 
 int /*<<< orphan*/  temp_sensor_ctrl ; 

__attribute__((used)) static int ti_bandgap_power(struct ti_bandgap *bgp, bool on)
{
	int i;

	if (!TI_BANDGAP_HAS(bgp, POWER_SWITCH))
		return -ENOTSUPP;

	for (i = 0; i < bgp->conf->sensor_count; i++)
		/* active on 0 */
		RMW_BITS(bgp, i, temp_sensor_ctrl, bgap_tempsoff_mask, !on);
	return 0;
}