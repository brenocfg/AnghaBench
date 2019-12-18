#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pp_hwmgr {int dummy; } ;
struct phm_clock_and_voltage_limits {unsigned long sclk; unsigned long mclk; unsigned long vddc; unsigned long vddci; } ;
struct TYPE_5__ {TYPE_1__* entries; } ;
struct TYPE_4__ {int /*<<< orphan*/  usVddci; int /*<<< orphan*/  usVddc; int /*<<< orphan*/  usMclkLow; scalar_t__ ucMclkHigh; int /*<<< orphan*/  usSclkLow; scalar_t__ ucSclkHigh; } ;
typedef  TYPE_2__ ATOM_PPLIB_Clock_Voltage_Limit_Table ;

/* Variables and functions */
 unsigned long le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_clock_voltage_limit(struct pp_hwmgr *hwmgr,
			struct phm_clock_and_voltage_limits *limits,
			const ATOM_PPLIB_Clock_Voltage_Limit_Table *table)
{
	limits->sclk = ((unsigned long)table->entries[0].ucSclkHigh << 16) |
			le16_to_cpu(table->entries[0].usSclkLow);
	limits->mclk = ((unsigned long)table->entries[0].ucMclkHigh << 16) |
			le16_to_cpu(table->entries[0].usMclkLow);
	limits->vddc = (unsigned long)le16_to_cpu(table->entries[0].usVddc);
	limits->vddci = (unsigned long)le16_to_cpu(table->entries[0].usVddci);

	return 0;
}