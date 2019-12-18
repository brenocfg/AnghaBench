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
typedef  int u8 ;

/* Variables and functions */
#define  COMP_BABBLE_DETECTED_ERROR 163 
#define  COMP_BANDWIDTH_ERROR 162 
#define  COMP_BANDWIDTH_OVERRUN_ERROR 161 
#define  COMP_COMMAND_ABORTED 160 
#define  COMP_COMMAND_RING_STOPPED 159 
#define  COMP_CONTEXT_STATE_ERROR 158 
#define  COMP_DATA_BUFFER_ERROR 157 
#define  COMP_ENDPOINT_NOT_ENABLED_ERROR 156 
#define  COMP_EVENT_LOST_ERROR 155 
#define  COMP_EVENT_RING_FULL_ERROR 154 
#define  COMP_INCOMPATIBLE_DEVICE_ERROR 153 
#define  COMP_INVALID 152 
#define  COMP_INVALID_STREAM_ID_ERROR 151 
#define  COMP_INVALID_STREAM_TYPE_ERROR 150 
#define  COMP_ISOCH_BUFFER_OVERRUN 149 
#define  COMP_MAX_EXIT_LATENCY_TOO_LARGE_ERROR 148 
#define  COMP_MISSED_SERVICE_ERROR 147 
#define  COMP_NO_PING_RESPONSE_ERROR 146 
#define  COMP_NO_SLOTS_AVAILABLE_ERROR 145 
#define  COMP_PARAMETER_ERROR 144 
#define  COMP_RESOURCE_ERROR 143 
#define  COMP_RING_OVERRUN 142 
#define  COMP_RING_UNDERRUN 141 
#define  COMP_SECONDARY_BANDWIDTH_ERROR 140 
#define  COMP_SHORT_PACKET 139 
#define  COMP_SLOT_NOT_ENABLED_ERROR 138 
#define  COMP_SPLIT_TRANSACTION_ERROR 137 
#define  COMP_STALL_ERROR 136 
#define  COMP_STOPPED 135 
#define  COMP_STOPPED_LENGTH_INVALID 134 
#define  COMP_STOPPED_SHORT_PACKET 133 
#define  COMP_SUCCESS 132 
#define  COMP_TRB_ERROR 131 
#define  COMP_UNDEFINED_ERROR 130 
#define  COMP_USB_TRANSACTION_ERROR 129 
#define  COMP_VF_EVENT_RING_FULL_ERROR 128 

__attribute__((used)) static inline const char *xhci_trb_comp_code_string(u8 status)
{
	switch (status) {
	case COMP_INVALID:
		return "Invalid";
	case COMP_SUCCESS:
		return "Success";
	case COMP_DATA_BUFFER_ERROR:
		return "Data Buffer Error";
	case COMP_BABBLE_DETECTED_ERROR:
		return "Babble Detected";
	case COMP_USB_TRANSACTION_ERROR:
		return "USB Transaction Error";
	case COMP_TRB_ERROR:
		return "TRB Error";
	case COMP_STALL_ERROR:
		return "Stall Error";
	case COMP_RESOURCE_ERROR:
		return "Resource Error";
	case COMP_BANDWIDTH_ERROR:
		return "Bandwidth Error";
	case COMP_NO_SLOTS_AVAILABLE_ERROR:
		return "No Slots Available Error";
	case COMP_INVALID_STREAM_TYPE_ERROR:
		return "Invalid Stream Type Error";
	case COMP_SLOT_NOT_ENABLED_ERROR:
		return "Slot Not Enabled Error";
	case COMP_ENDPOINT_NOT_ENABLED_ERROR:
		return "Endpoint Not Enabled Error";
	case COMP_SHORT_PACKET:
		return "Short Packet";
	case COMP_RING_UNDERRUN:
		return "Ring Underrun";
	case COMP_RING_OVERRUN:
		return "Ring Overrun";
	case COMP_VF_EVENT_RING_FULL_ERROR:
		return "VF Event Ring Full Error";
	case COMP_PARAMETER_ERROR:
		return "Parameter Error";
	case COMP_BANDWIDTH_OVERRUN_ERROR:
		return "Bandwidth Overrun Error";
	case COMP_CONTEXT_STATE_ERROR:
		return "Context State Error";
	case COMP_NO_PING_RESPONSE_ERROR:
		return "No Ping Response Error";
	case COMP_EVENT_RING_FULL_ERROR:
		return "Event Ring Full Error";
	case COMP_INCOMPATIBLE_DEVICE_ERROR:
		return "Incompatible Device Error";
	case COMP_MISSED_SERVICE_ERROR:
		return "Missed Service Error";
	case COMP_COMMAND_RING_STOPPED:
		return "Command Ring Stopped";
	case COMP_COMMAND_ABORTED:
		return "Command Aborted";
	case COMP_STOPPED:
		return "Stopped";
	case COMP_STOPPED_LENGTH_INVALID:
		return "Stopped - Length Invalid";
	case COMP_STOPPED_SHORT_PACKET:
		return "Stopped - Short Packet";
	case COMP_MAX_EXIT_LATENCY_TOO_LARGE_ERROR:
		return "Max Exit Latency Too Large Error";
	case COMP_ISOCH_BUFFER_OVERRUN:
		return "Isoch Buffer Overrun";
	case COMP_EVENT_LOST_ERROR:
		return "Event Lost Error";
	case COMP_UNDEFINED_ERROR:
		return "Undefined Error";
	case COMP_INVALID_STREAM_ID_ERROR:
		return "Invalid Stream ID Error";
	case COMP_SECONDARY_BANDWIDTH_ERROR:
		return "Secondary Bandwidth Error";
	case COMP_SPLIT_TRANSACTION_ERROR:
		return "Split Transaction Error";
	default:
		return "Unknown!!";
	}
}