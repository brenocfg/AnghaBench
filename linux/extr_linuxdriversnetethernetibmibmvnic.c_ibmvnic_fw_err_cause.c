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
typedef  int u16 ;

/* Variables and functions */
#define  ADAPTER_PROBLEM 134 
#define  BUS_PROBLEM 133 
#define  DD_PROBLEM 132 
#define  EEH_RECOVERY 131 
#define  FW_PROBLEM 130 
#define  FW_UPDATED 129 
#define  LOW_MEMORY 128 

__attribute__((used)) static const char *ibmvnic_fw_err_cause(u16 cause)
{
	switch (cause) {
	case ADAPTER_PROBLEM:
		return "adapter problem";
	case BUS_PROBLEM:
		return "bus problem";
	case FW_PROBLEM:
		return "firmware problem";
	case DD_PROBLEM:
		return "device driver problem";
	case EEH_RECOVERY:
		return "EEH recovery";
	case FW_UPDATED:
		return "firmware updated";
	case LOW_MEMORY:
		return "low Memory";
	default:
		return "unknown";
	}
}