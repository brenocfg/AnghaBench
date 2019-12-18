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
typedef  int u32 ;

/* Variables and functions */
 int BLOCK_INFO_BLK_ID (int) ; 
 int BLOCK_INFO_BLK_TYPE (int) ; 
#define  D71_BLK_TYPE_CU 135 
#define  D71_BLK_TYPE_CU_MERGER 134 
#define  D71_BLK_TYPE_CU_SCALER 133 
#define  D71_BLK_TYPE_CU_SPLITTER 132 
#define  D71_BLK_TYPE_DOU 131 
#define  D71_BLK_TYPE_DOU_IPS 130 
#define  D71_BLK_TYPE_LPU_LAYER 129 
#define  D71_BLK_TYPE_LPU_WB_LAYER 128 
 int D71_PIPELINE_MAX_LAYERS ; 
 int D71_PIPELINE_MAX_SCALERS ; 
 int KOMEDA_COMPONENT_COMPIZ0 ; 
 int KOMEDA_COMPONENT_IPS0 ; 
 int KOMEDA_COMPONENT_LAYER0 ; 
 int KOMEDA_COMPONENT_MERGER ; 
 int KOMEDA_COMPONENT_SCALER0 ; 
 int KOMEDA_COMPONENT_SPLITTER ; 
 int KOMEDA_COMPONENT_TIMING_CTRLR ; 
 int KOMEDA_COMPONENT_WB_LAYER ; 

__attribute__((used)) static void get_resources_id(u32 hw_id, u32 *pipe_id, u32 *comp_id)
{
	u32 id = BLOCK_INFO_BLK_ID(hw_id);
	u32 pipe = id;

	switch (BLOCK_INFO_BLK_TYPE(hw_id)) {
	case D71_BLK_TYPE_LPU_WB_LAYER:
		id = KOMEDA_COMPONENT_WB_LAYER;
		break;
	case D71_BLK_TYPE_CU_SPLITTER:
		id = KOMEDA_COMPONENT_SPLITTER;
		break;
	case D71_BLK_TYPE_CU_SCALER:
		pipe = id / D71_PIPELINE_MAX_SCALERS;
		id %= D71_PIPELINE_MAX_SCALERS;
		id += KOMEDA_COMPONENT_SCALER0;
		break;
	case D71_BLK_TYPE_CU:
		id += KOMEDA_COMPONENT_COMPIZ0;
		break;
	case D71_BLK_TYPE_LPU_LAYER:
		pipe = id / D71_PIPELINE_MAX_LAYERS;
		id %= D71_PIPELINE_MAX_LAYERS;
		id += KOMEDA_COMPONENT_LAYER0;
		break;
	case D71_BLK_TYPE_DOU_IPS:
		id += KOMEDA_COMPONENT_IPS0;
		break;
	case D71_BLK_TYPE_CU_MERGER:
		id = KOMEDA_COMPONENT_MERGER;
		break;
	case D71_BLK_TYPE_DOU:
		id = KOMEDA_COMPONENT_TIMING_CTRLR;
		break;
	default:
		id = 0xFFFFFFFF;
	}

	if (comp_id)
		*comp_id = id;

	if (pipe_id)
		*pipe_id = pipe;
}