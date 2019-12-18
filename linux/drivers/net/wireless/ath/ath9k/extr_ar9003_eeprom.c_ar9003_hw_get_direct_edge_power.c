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
struct cal_ctl_data_5g {int /*<<< orphan*/ * ctlEdges; } ;
struct cal_ctl_data_2g {int /*<<< orphan*/ * ctlEdges; } ;
struct ar9300_eeprom {struct cal_ctl_data_5g* ctlPowerData_5G; struct cal_ctl_data_2g* ctlPowerData_2G; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_EDGE_TPOWER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 ar9003_hw_get_direct_edge_power(struct ar9300_eeprom *eep,
					   int idx,
					   int edge,
					   bool is2GHz)
{
	struct cal_ctl_data_2g *ctl_2g = eep->ctlPowerData_2G;
	struct cal_ctl_data_5g *ctl_5g = eep->ctlPowerData_5G;

	if (is2GHz)
		return CTL_EDGE_TPOWER(ctl_2g[idx].ctlEdges[edge]);
	else
		return CTL_EDGE_TPOWER(ctl_5g[idx].ctlEdges[edge]);
}