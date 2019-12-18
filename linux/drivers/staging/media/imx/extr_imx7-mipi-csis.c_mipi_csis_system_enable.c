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
struct TYPE_2__ {int num_data_lanes; } ;
struct csi_state {TYPE_1__ bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_CSIS_CMN_CTRL ; 
 int MIPI_CSIS_CMN_CTRL_ENABLE ; 
 int /*<<< orphan*/  MIPI_CSIS_DPHYCTRL ; 
 int MIPI_CSIS_DPHYCTRL_ENABLE ; 
 int mipi_csis_read (struct csi_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_csis_write (struct csi_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mipi_csis_system_enable(struct csi_state *state, int on)
{
	u32 val, mask;

	val = mipi_csis_read(state, MIPI_CSIS_CMN_CTRL);
	if (on)
		val |= MIPI_CSIS_CMN_CTRL_ENABLE;
	else
		val &= ~MIPI_CSIS_CMN_CTRL_ENABLE;
	mipi_csis_write(state, MIPI_CSIS_CMN_CTRL, val);

	val = mipi_csis_read(state, MIPI_CSIS_DPHYCTRL);
	val &= ~MIPI_CSIS_DPHYCTRL_ENABLE;
	if (on) {
		mask = (1 << (state->bus.num_data_lanes + 1)) - 1;
		val |= (mask & MIPI_CSIS_DPHYCTRL_ENABLE);
	}
	mipi_csis_write(state, MIPI_CSIS_DPHYCTRL, val);
}