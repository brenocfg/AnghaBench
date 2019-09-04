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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int SVGA_CAP_3D ; 
 int SVGA_CAP_8BIT_EMULATION ; 
 int SVGA_CAP_ALPHA_CURSOR ; 
 int SVGA_CAP_CMD_BUFFERS_2 ; 
 int SVGA_CAP_COMMAND_BUFFERS ; 
 int SVGA_CAP_CURSOR ; 
 int SVGA_CAP_CURSOR_BYPASS ; 
 int SVGA_CAP_CURSOR_BYPASS_2 ; 
 int SVGA_CAP_DISPLAY_TOPOLOGY ; 
 int SVGA_CAP_DX ; 
 int SVGA_CAP_EXTENDED_FIFO ; 
 int SVGA_CAP_GBOBJECTS ; 
 int SVGA_CAP_GMR ; 
 int SVGA_CAP_GMR2 ; 
 int SVGA_CAP_HP_CMD_QUEUE ; 
 int SVGA_CAP_IRQMASK ; 
 int SVGA_CAP_MULTIMON ; 
 int SVGA_CAP_PITCHLOCK ; 
 int SVGA_CAP_RECT_COPY ; 
 int SVGA_CAP_SCREEN_OBJECT_2 ; 
 int SVGA_CAP_TRACES ; 

__attribute__((used)) static void vmw_print_capabilities(uint32_t capabilities)
{
	DRM_INFO("Capabilities:\n");
	if (capabilities & SVGA_CAP_RECT_COPY)
		DRM_INFO("  Rect copy.\n");
	if (capabilities & SVGA_CAP_CURSOR)
		DRM_INFO("  Cursor.\n");
	if (capabilities & SVGA_CAP_CURSOR_BYPASS)
		DRM_INFO("  Cursor bypass.\n");
	if (capabilities & SVGA_CAP_CURSOR_BYPASS_2)
		DRM_INFO("  Cursor bypass 2.\n");
	if (capabilities & SVGA_CAP_8BIT_EMULATION)
		DRM_INFO("  8bit emulation.\n");
	if (capabilities & SVGA_CAP_ALPHA_CURSOR)
		DRM_INFO("  Alpha cursor.\n");
	if (capabilities & SVGA_CAP_3D)
		DRM_INFO("  3D.\n");
	if (capabilities & SVGA_CAP_EXTENDED_FIFO)
		DRM_INFO("  Extended Fifo.\n");
	if (capabilities & SVGA_CAP_MULTIMON)
		DRM_INFO("  Multimon.\n");
	if (capabilities & SVGA_CAP_PITCHLOCK)
		DRM_INFO("  Pitchlock.\n");
	if (capabilities & SVGA_CAP_IRQMASK)
		DRM_INFO("  Irq mask.\n");
	if (capabilities & SVGA_CAP_DISPLAY_TOPOLOGY)
		DRM_INFO("  Display Topology.\n");
	if (capabilities & SVGA_CAP_GMR)
		DRM_INFO("  GMR.\n");
	if (capabilities & SVGA_CAP_TRACES)
		DRM_INFO("  Traces.\n");
	if (capabilities & SVGA_CAP_GMR2)
		DRM_INFO("  GMR2.\n");
	if (capabilities & SVGA_CAP_SCREEN_OBJECT_2)
		DRM_INFO("  Screen Object 2.\n");
	if (capabilities & SVGA_CAP_COMMAND_BUFFERS)
		DRM_INFO("  Command Buffers.\n");
	if (capabilities & SVGA_CAP_CMD_BUFFERS_2)
		DRM_INFO("  Command Buffers 2.\n");
	if (capabilities & SVGA_CAP_GBOBJECTS)
		DRM_INFO("  Guest Backed Resources.\n");
	if (capabilities & SVGA_CAP_DX)
		DRM_INFO("  DX Features.\n");
	if (capabilities & SVGA_CAP_HP_CMD_QUEUE)
		DRM_INFO("  HP Command Queue.\n");
}