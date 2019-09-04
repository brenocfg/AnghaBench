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
typedef  int u64 ;
struct TYPE_4__ {TYPE_1__* states; int /*<<< orphan*/  state_count; } ;
struct powernow_k8_data {int irt; int rvo; int exttype; int plllock; int vidmvs; int vstable; TYPE_2__ acpi_data; } ;
struct TYPE_3__ {int control; } ;

/* Variables and functions */
 int EXT_TYPE_MASK ; 
 int EXT_TYPE_SHIFT ; 
 int IRT_MASK ; 
 int IRT_SHIFT ; 
 int MVS_MASK ; 
 int MVS_SHIFT ; 
 int PLL_L_MASK ; 
 int PLL_L_SHIFT ; 
 int RVO_MASK ; 
 int RVO_SHIFT ; 
 int VST_MASK ; 
 int VST_SHIFT ; 

__attribute__((used)) static void powernow_k8_acpi_pst_values(struct powernow_k8_data *data,
		unsigned int index)
{
	u64 control;

	if (!data->acpi_data.state_count)
		return;

	control = data->acpi_data.states[index].control;
	data->irt = (control >> IRT_SHIFT) & IRT_MASK;
	data->rvo = (control >> RVO_SHIFT) & RVO_MASK;
	data->exttype = (control >> EXT_TYPE_SHIFT) & EXT_TYPE_MASK;
	data->plllock = (control >> PLL_L_SHIFT) & PLL_L_MASK;
	data->vidmvs = 1 << ((control >> MVS_SHIFT) & MVS_MASK);
	data->vstable = (control >> VST_SHIFT) & VST_MASK;
}