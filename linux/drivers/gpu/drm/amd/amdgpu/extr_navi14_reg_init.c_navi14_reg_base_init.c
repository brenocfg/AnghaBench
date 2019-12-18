#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int /*<<< orphan*/ *** reg_offset; } ;
struct TYPE_28__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_27__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_26__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_25__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_24__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_23__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_22__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_21__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_20__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_19__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_18__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_17__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_16__ {int /*<<< orphan*/ * instance; } ;
struct TYPE_15__ {int /*<<< orphan*/ * instance; } ;

/* Variables and functions */
 TYPE_14__ ATHUB_BASE ; 
 size_t ATHUB_HWIP ; 
 TYPE_13__ CLK_BASE ; 
 size_t CLK_HWIP ; 
 size_t DCE_HWIP ; 
 TYPE_12__ DF_BASE ; 
 size_t DF_HWIP ; 
 TYPE_11__ DMU_BASE ; 
 TYPE_10__ GC_BASE ; 
 size_t GC_HWIP ; 
 TYPE_9__ HDP_BASE ; 
 size_t HDP_HWIP ; 
 int MAX_INSTANCE ; 
 TYPE_8__ MMHUB_BASE ; 
 size_t MMHUB_HWIP ; 
 TYPE_7__ MP0_BASE ; 
 size_t MP0_HWIP ; 
 TYPE_6__ MP1_BASE ; 
 size_t MP1_HWIP ; 
 TYPE_5__ NBIF0_BASE ; 
 size_t NBIO_HWIP ; 
 TYPE_4__ OSSSYS_BASE ; 
 size_t OSSSYS_HWIP ; 
 size_t SDMA0_HWIP ; 
 size_t SDMA1_HWIP ; 
 TYPE_3__ SMUIO_BASE ; 
 size_t SMUIO_HWIP ; 
 TYPE_2__ THM_BASE ; 
 size_t THM_HWIP ; 
 TYPE_1__ UVD0_BASE ; 
 size_t VCN_HWIP ; 

int navi14_reg_base_init(struct amdgpu_device *adev)
{
	int i;

	for (i = 0 ; i < MAX_INSTANCE ; ++i) {
		adev->reg_offset[GC_HWIP][i] = (uint32_t *)(&(GC_BASE.instance[i]));
		adev->reg_offset[HDP_HWIP][i] = (uint32_t *)(&(HDP_BASE.instance[i]));
		adev->reg_offset[MMHUB_HWIP][i] = (uint32_t *)(&(MMHUB_BASE.instance[i]));
		adev->reg_offset[ATHUB_HWIP][i] = (uint32_t *)(&(ATHUB_BASE.instance[i]));
		adev->reg_offset[NBIO_HWIP][i] = (uint32_t *)(&(NBIF0_BASE.instance[i]));
		adev->reg_offset[MP0_HWIP][i] = (uint32_t *)(&(MP0_BASE.instance[i]));
		adev->reg_offset[MP1_HWIP][i] = (uint32_t *)(&(MP1_BASE.instance[i]));
		adev->reg_offset[VCN_HWIP][i] = (uint32_t *)(&(UVD0_BASE.instance[i]));
		adev->reg_offset[DF_HWIP][i] = (uint32_t *)(&(DF_BASE.instance[i]));
		adev->reg_offset[DCE_HWIP][i] = (uint32_t *)(&(DMU_BASE.instance[i]));
		adev->reg_offset[OSSSYS_HWIP][i] = (uint32_t *)(&(OSSSYS_BASE.instance[i]));
		adev->reg_offset[SDMA0_HWIP][i] = (uint32_t *)(&(GC_BASE.instance[i]));
		adev->reg_offset[SDMA1_HWIP][i] = (uint32_t *)(&(GC_BASE.instance[i]));
		adev->reg_offset[SMUIO_HWIP][i] = (uint32_t *)(&(SMUIO_BASE.instance[i]));
		adev->reg_offset[THM_HWIP][i] = (uint32_t *)(&(THM_BASE.instance[i]));
		adev->reg_offset[CLK_HWIP][i] = (uint32_t *)(&(CLK_BASE.instance[i]));
	}

	return 0;
}