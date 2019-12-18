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
typedef  enum dm_validation_status { ____Placeholder_dm_validation_status } dm_validation_status ;

/* Variables and functions */
#define  DML_FAIL_CURSOR_SUPPORT 149 
#define  DML_FAIL_DIO_SUPPORT 148 
#define  DML_FAIL_DISPCLK_DPPCLK 147 
#define  DML_FAIL_DSC_CLK_REQUIRED 146 
#define  DML_FAIL_DSC_INPUT_BPC 145 
#define  DML_FAIL_NOT_ENOUGH_DSC 144 
#define  DML_FAIL_NUM_OTG 143 
#define  DML_FAIL_PITCH_SUPPORT 142 
#define  DML_FAIL_PREFETCH_SUPPORT 141 
#define  DML_FAIL_PTE_BUFFER_SIZE 140 
#define  DML_FAIL_REORDERING_BUFFER 139 
#define  DML_FAIL_SCALE_RATIO_TAP 138 
#define  DML_FAIL_SOURCE_PIXEL_FORMAT 137 
#define  DML_FAIL_TOTAL_AVAILABLE_PIPES 136 
#define  DML_FAIL_TOTAL_V_ACTIVE_BW 135 
#define  DML_FAIL_URGENT_LATENCY 134 
#define  DML_FAIL_VIEWPORT_SIZE 133 
#define  DML_FAIL_V_RATIO_PREFETCH 132 
#define  DML_FAIL_WRITEBACK_LATENCY 131 
#define  DML_FAIL_WRITEBACK_MODE 130 
#define  DML_FAIL_WRITEBACK_SCALE_RATIO_TAP 129 
#define  DML_VALIDATION_OK 128 

const char *dml_get_status_message(enum dm_validation_status status)
{
	switch (status) {
	case DML_VALIDATION_OK:                   return "Validation OK";
	case DML_FAIL_SCALE_RATIO_TAP:            return "Scale ratio/tap";
	case DML_FAIL_SOURCE_PIXEL_FORMAT:        return "Source pixel format";
	case DML_FAIL_VIEWPORT_SIZE:              return "Viewport size";
	case DML_FAIL_TOTAL_V_ACTIVE_BW:          return "Total vertical active bandwidth";
	case DML_FAIL_DIO_SUPPORT:                return "DIO support";
	case DML_FAIL_NOT_ENOUGH_DSC:             return "Not enough DSC Units";
	case DML_FAIL_DSC_CLK_REQUIRED:           return "DSC clock required";
	case DML_FAIL_URGENT_LATENCY:             return "Urgent latency";
	case DML_FAIL_REORDERING_BUFFER:          return "Re-ordering buffer";
	case DML_FAIL_DISPCLK_DPPCLK:             return "Dispclk and Dppclk";
	case DML_FAIL_TOTAL_AVAILABLE_PIPES:      return "Total available pipes";
	case DML_FAIL_NUM_OTG:                    return "Number of OTG";
	case DML_FAIL_WRITEBACK_MODE:             return "Writeback mode";
	case DML_FAIL_WRITEBACK_LATENCY:          return "Writeback latency";
	case DML_FAIL_WRITEBACK_SCALE_RATIO_TAP:  return "Writeback scale ratio/tap";
	case DML_FAIL_CURSOR_SUPPORT:             return "Cursor support";
	case DML_FAIL_PITCH_SUPPORT:              return "Pitch support";
	case DML_FAIL_PTE_BUFFER_SIZE:            return "PTE buffer size";
	case DML_FAIL_DSC_INPUT_BPC:              return "DSC input bpc";
	case DML_FAIL_PREFETCH_SUPPORT:           return "Prefetch support";
	case DML_FAIL_V_RATIO_PREFETCH:           return "Vertical ratio prefetch";
	default:                                  return "Unknown Status";
	}
}