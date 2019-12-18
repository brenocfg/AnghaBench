#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ti_bandgap {TYPE_1__* conf; } ;
struct temp_sensor_registers {int bgap_eocz_mask; int /*<<< orphan*/  temp_sensor_ctrl; } ;
struct TYPE_4__ {struct temp_sensor_registers* registers; } ;
struct TYPE_3__ {TYPE_2__* sensors; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_CONFIG ; 
 int /*<<< orphan*/  RMW_BITS (struct ti_bandgap*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TI_BANDGAP_HAS (struct ti_bandgap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgap_mode_ctrl ; 
 int /*<<< orphan*/  bgap_soc_mask ; 
 int /*<<< orphan*/  mode_ctrl_mask ; 
 int /*<<< orphan*/  temp_sensor_ctrl ; 
 int ti_bandgap_readl (struct ti_bandgap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_bandgap_force_single_read(struct ti_bandgap *bgp, int id)
{
	u32 counter = 1000;
	struct temp_sensor_registers *tsr;

	/* Select single conversion mode */
	if (TI_BANDGAP_HAS(bgp, MODE_CONFIG))
		RMW_BITS(bgp, id, bgap_mode_ctrl, mode_ctrl_mask, 0);

	/* Start of Conversion = 1 */
	RMW_BITS(bgp, id, temp_sensor_ctrl, bgap_soc_mask, 1);

	/* Wait for EOCZ going up */
	tsr = bgp->conf->sensors[id].registers;

	while (--counter) {
		if (ti_bandgap_readl(bgp, tsr->temp_sensor_ctrl) &
		    tsr->bgap_eocz_mask)
			break;
	}

	/* Start of Conversion = 0 */
	RMW_BITS(bgp, id, temp_sensor_ctrl, bgap_soc_mask, 0);

	/* Wait for EOCZ going down */
	counter = 1000;
	while (--counter) {
		if (!(ti_bandgap_readl(bgp, tsr->temp_sensor_ctrl) &
		      tsr->bgap_eocz_mask))
			break;
	}

	return 0;
}