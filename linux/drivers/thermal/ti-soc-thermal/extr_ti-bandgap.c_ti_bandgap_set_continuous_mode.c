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
 int /*<<< orphan*/  RMW_BITS (struct ti_bandgap*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bgap_mode_ctrl ; 
 int /*<<< orphan*/  mode_ctrl_mask ; 
 int /*<<< orphan*/  ti_bandgap_force_single_read (struct ti_bandgap*,int) ; 

__attribute__((used)) static int ti_bandgap_set_continuous_mode(struct ti_bandgap *bgp)
{
	int i;

	for (i = 0; i < bgp->conf->sensor_count; i++) {
		/* Perform a single read just before enabling continuous */
		ti_bandgap_force_single_read(bgp, i);
		RMW_BITS(bgp, i, bgap_mode_ctrl, mode_ctrl_mask, 1);
	}

	return 0;
}