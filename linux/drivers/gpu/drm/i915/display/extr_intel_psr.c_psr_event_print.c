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
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int PSR_EVENT_FRONT_BUFFER_MODIFY ; 
 int PSR_EVENT_GRAPHICS_RESET ; 
 int PSR_EVENT_HDCP_ENABLE ; 
 int PSR_EVENT_KVMR_SESSION_ENABLE ; 
 int PSR_EVENT_LPSP_MODE_EXIT ; 
 int PSR_EVENT_MEMORY_UP ; 
 int PSR_EVENT_PCH_INTERRUPT ; 
 int PSR_EVENT_PIPE_REGISTERS_UPDATE ; 
 int PSR_EVENT_PSR2_DISABLED ; 
 int PSR_EVENT_PSR2_WD_TIMER_EXPIRE ; 
 int PSR_EVENT_PSR_DISABLE ; 
 int PSR_EVENT_REGISTER_UPDATE ; 
 int PSR_EVENT_SU_CRC_FIFO_UNDERRUN ; 
 int PSR_EVENT_SU_DIRTY_FIFO_UNDERRUN ; 
 int PSR_EVENT_VBI_ENABLE ; 
 int PSR_EVENT_WD_TIMER_EXPIRE ; 

__attribute__((used)) static void psr_event_print(u32 val, bool psr2_enabled)
{
	DRM_DEBUG_KMS("PSR exit events: 0x%x\n", val);
	if (val & PSR_EVENT_PSR2_WD_TIMER_EXPIRE)
		DRM_DEBUG_KMS("\tPSR2 watchdog timer expired\n");
	if ((val & PSR_EVENT_PSR2_DISABLED) && psr2_enabled)
		DRM_DEBUG_KMS("\tPSR2 disabled\n");
	if (val & PSR_EVENT_SU_DIRTY_FIFO_UNDERRUN)
		DRM_DEBUG_KMS("\tSU dirty FIFO underrun\n");
	if (val & PSR_EVENT_SU_CRC_FIFO_UNDERRUN)
		DRM_DEBUG_KMS("\tSU CRC FIFO underrun\n");
	if (val & PSR_EVENT_GRAPHICS_RESET)
		DRM_DEBUG_KMS("\tGraphics reset\n");
	if (val & PSR_EVENT_PCH_INTERRUPT)
		DRM_DEBUG_KMS("\tPCH interrupt\n");
	if (val & PSR_EVENT_MEMORY_UP)
		DRM_DEBUG_KMS("\tMemory up\n");
	if (val & PSR_EVENT_FRONT_BUFFER_MODIFY)
		DRM_DEBUG_KMS("\tFront buffer modification\n");
	if (val & PSR_EVENT_WD_TIMER_EXPIRE)
		DRM_DEBUG_KMS("\tPSR watchdog timer expired\n");
	if (val & PSR_EVENT_PIPE_REGISTERS_UPDATE)
		DRM_DEBUG_KMS("\tPIPE registers updated\n");
	if (val & PSR_EVENT_REGISTER_UPDATE)
		DRM_DEBUG_KMS("\tRegister updated\n");
	if (val & PSR_EVENT_HDCP_ENABLE)
		DRM_DEBUG_KMS("\tHDCP enabled\n");
	if (val & PSR_EVENT_KVMR_SESSION_ENABLE)
		DRM_DEBUG_KMS("\tKVMR session enabled\n");
	if (val & PSR_EVENT_VBI_ENABLE)
		DRM_DEBUG_KMS("\tVBI enabled\n");
	if (val & PSR_EVENT_LPSP_MODE_EXIT)
		DRM_DEBUG_KMS("\tLPSP mode exited\n");
	if ((val & PSR_EVENT_PSR_DISABLE) && !psr2_enabled)
		DRM_DEBUG_KMS("\tPSR disabled\n");
}