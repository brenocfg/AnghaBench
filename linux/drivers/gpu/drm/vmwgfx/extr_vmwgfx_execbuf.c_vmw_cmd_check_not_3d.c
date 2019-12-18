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
struct vmw_sw_context {int /*<<< orphan*/  kernel; } ;
struct vmw_private {int dummy; } ;
typedef  int /*<<< orphan*/  SVGAFifoCmdUpdate ;
typedef  int /*<<< orphan*/  SVGAFifoCmdDefineGMRFB ;
typedef  int /*<<< orphan*/  SVGAFifoCmdBlitGMRFBToScreen ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
#define  SVGA_CMD_BLIT_GMRFB_TO_SCREEN 131 
#define  SVGA_CMD_BLIT_SCREEN_TO_GMRFB 130 
#define  SVGA_CMD_DEFINE_GMRFB 129 
#define  SVGA_CMD_UPDATE 128 
 int /*<<< orphan*/  VMW_DEBUG_USER (char*,int) ; 
 scalar_t__ unlikely (int) ; 
 int vmw_cmd_check_define_gmrfb (struct vmw_private*,struct vmw_sw_context*,void*) ; 

__attribute__((used)) static int vmw_cmd_check_not_3d(struct vmw_private *dev_priv,
				struct vmw_sw_context *sw_context,
				void *buf, uint32_t *size)
{
	uint32_t size_remaining = *size;
	uint32_t cmd_id;

	cmd_id = ((uint32_t *)buf)[0];
	switch (cmd_id) {
	case SVGA_CMD_UPDATE:
		*size = sizeof(uint32_t) + sizeof(SVGAFifoCmdUpdate);
		break;
	case SVGA_CMD_DEFINE_GMRFB:
		*size = sizeof(uint32_t) + sizeof(SVGAFifoCmdDefineGMRFB);
		break;
	case SVGA_CMD_BLIT_GMRFB_TO_SCREEN:
		*size = sizeof(uint32_t) + sizeof(SVGAFifoCmdBlitGMRFBToScreen);
		break;
	case SVGA_CMD_BLIT_SCREEN_TO_GMRFB:
		*size = sizeof(uint32_t) + sizeof(SVGAFifoCmdBlitGMRFBToScreen);
		break;
	default:
		VMW_DEBUG_USER("Unsupported SVGA command: %u.\n", cmd_id);
		return -EINVAL;
	}

	if (*size > size_remaining) {
		VMW_DEBUG_USER("Invalid SVGA command (size mismatch): %u.\n",
			       cmd_id);
		return -EINVAL;
	}

	if (unlikely(!sw_context->kernel)) {
		VMW_DEBUG_USER("Kernel only SVGA command: %u.\n", cmd_id);
		return -EPERM;
	}

	if (cmd_id == SVGA_CMD_DEFINE_GMRFB)
		return vmw_cmd_check_define_gmrfb(dev_priv, sw_context, buf);

	return 0;
}