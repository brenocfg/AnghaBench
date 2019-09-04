#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct vmw_cmd_entry {char* cmd_name; } ;
struct TYPE_2__ {size_t size; size_t id; } ;
typedef  int /*<<< orphan*/  SVGAFifoCmdUpdate ;
typedef  int /*<<< orphan*/  SVGAFifoCmdDefineGMRFB ;
typedef  int /*<<< orphan*/  SVGAFifoCmdBlitGMRFBToScreen ;
typedef  TYPE_1__ SVGA3dCmdHeader ;

/* Variables and functions */
 scalar_t__ SVGA_3D_CMD_BASE ; 
 size_t SVGA_3D_CMD_MAX ; 
#define  SVGA_CMD_BLIT_GMRFB_TO_SCREEN 131 
#define  SVGA_CMD_BLIT_SCREEN_TO_GMRFB 130 
#define  SVGA_CMD_DEFINE_GMRFB 129 
 size_t SVGA_CMD_MAX ; 
#define  SVGA_CMD_UPDATE 128 
 struct vmw_cmd_entry* vmw_cmd_entries ; 

bool vmw_cmd_describe(const void *buf, u32 *size, char const **cmd)
{
	u32 cmd_id = ((u32 *) buf)[0];

	if (cmd_id >= SVGA_CMD_MAX) {
		SVGA3dCmdHeader *header = (SVGA3dCmdHeader *) buf;
		const struct vmw_cmd_entry *entry;

		*size = header->size + sizeof(SVGA3dCmdHeader);
		cmd_id = header->id;
		if (cmd_id >= SVGA_3D_CMD_MAX)
			return false;

		cmd_id -= SVGA_3D_CMD_BASE;
		entry = &vmw_cmd_entries[cmd_id];
		*cmd = entry->cmd_name;
		return true;
	}

	switch (cmd_id) {
	case SVGA_CMD_UPDATE:
		*cmd = "SVGA_CMD_UPDATE";
		*size = sizeof(u32) + sizeof(SVGAFifoCmdUpdate);
		break;
	case SVGA_CMD_DEFINE_GMRFB:
		*cmd = "SVGA_CMD_DEFINE_GMRFB";
		*size = sizeof(u32) + sizeof(SVGAFifoCmdDefineGMRFB);
		break;
	case SVGA_CMD_BLIT_GMRFB_TO_SCREEN:
		*cmd = "SVGA_CMD_BLIT_GMRFB_TO_SCREEN";
		*size = sizeof(u32) + sizeof(SVGAFifoCmdBlitGMRFBToScreen);
		break;
	case SVGA_CMD_BLIT_SCREEN_TO_GMRFB:
		*cmd = "SVGA_CMD_BLIT_SCREEN_TO_GMRFB";
		*size = sizeof(u32) + sizeof(SVGAFifoCmdBlitGMRFBToScreen);
		break;
	default:
		*cmd = "UNKNOWN";
		*size = 0;
		return false;
	}

	return true;
}