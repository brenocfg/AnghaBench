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
#define  IPW_FW_ERROR_ALLOC_FAIL 142 
#define  IPW_FW_ERROR_BAD_CHECKSUM 141 
#define  IPW_FW_ERROR_BAD_DATABASE 140 
#define  IPW_FW_ERROR_BAD_PARAM 139 
#define  IPW_FW_ERROR_DINO_ERROR 138 
#define  IPW_FW_ERROR_DMA_STATUS 137 
#define  IPW_FW_ERROR_DMA_UNDERRUN 136 
#define  IPW_FW_ERROR_EEPROM_ERROR 135 
#define  IPW_FW_ERROR_FAIL 134 
#define  IPW_FW_ERROR_FATAL_ERROR 133 
#define  IPW_FW_ERROR_MEMORY_OVERFLOW 132 
#define  IPW_FW_ERROR_MEMORY_UNDERFLOW 131 
#define  IPW_FW_ERROR_NMI_INTERRUPT 130 
#define  IPW_FW_ERROR_OK 129 
#define  IPW_FW_ERROR_SYSASSERT 128 

__attribute__((used)) static char *ipw_error_desc(u32 val)
{
	switch (val) {
	case IPW_FW_ERROR_OK:
		return "ERROR_OK";
	case IPW_FW_ERROR_FAIL:
		return "ERROR_FAIL";
	case IPW_FW_ERROR_MEMORY_UNDERFLOW:
		return "MEMORY_UNDERFLOW";
	case IPW_FW_ERROR_MEMORY_OVERFLOW:
		return "MEMORY_OVERFLOW";
	case IPW_FW_ERROR_BAD_PARAM:
		return "BAD_PARAM";
	case IPW_FW_ERROR_BAD_CHECKSUM:
		return "BAD_CHECKSUM";
	case IPW_FW_ERROR_NMI_INTERRUPT:
		return "NMI_INTERRUPT";
	case IPW_FW_ERROR_BAD_DATABASE:
		return "BAD_DATABASE";
	case IPW_FW_ERROR_ALLOC_FAIL:
		return "ALLOC_FAIL";
	case IPW_FW_ERROR_DMA_UNDERRUN:
		return "DMA_UNDERRUN";
	case IPW_FW_ERROR_DMA_STATUS:
		return "DMA_STATUS";
	case IPW_FW_ERROR_DINO_ERROR:
		return "DINO_ERROR";
	case IPW_FW_ERROR_EEPROM_ERROR:
		return "EEPROM_ERROR";
	case IPW_FW_ERROR_SYSASSERT:
		return "SYSASSERT";
	case IPW_FW_ERROR_FATAL_ERROR:
		return "FATAL_ERROR";
	default:
		return "UNKNOWN_ERROR";
	}
}