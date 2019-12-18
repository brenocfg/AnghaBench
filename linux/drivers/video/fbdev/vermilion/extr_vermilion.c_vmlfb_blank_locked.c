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
struct vml_par {int dummy; } ;
struct vml_info {int cur_blank_mode; int /*<<< orphan*/  pipe_disabled; struct vml_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  VML_PIPEACONF ; 
 int VML_PIPE_FORCE_BORDER ; 
 int VML_READ32 (struct vml_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VML_WRITE32 (struct vml_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmlfb_disable_pipe (struct vml_info*) ; 
 int /*<<< orphan*/  vmlfb_set_par_locked (struct vml_info*) ; 

__attribute__((used)) static int vmlfb_blank_locked(struct vml_info *vinfo)
{
	struct vml_par *par = vinfo->par;
	u32 cur = VML_READ32(par, VML_PIPEACONF);

	switch (vinfo->cur_blank_mode) {
	case FB_BLANK_UNBLANK:
		if (vinfo->pipe_disabled) {
			vmlfb_set_par_locked(vinfo);
		}
		VML_WRITE32(par, VML_PIPEACONF, cur & ~VML_PIPE_FORCE_BORDER);
		(void)VML_READ32(par, VML_PIPEACONF);
		break;
	case FB_BLANK_NORMAL:
		if (vinfo->pipe_disabled) {
			vmlfb_set_par_locked(vinfo);
		}
		VML_WRITE32(par, VML_PIPEACONF, cur | VML_PIPE_FORCE_BORDER);
		(void)VML_READ32(par, VML_PIPEACONF);
		break;
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
		if (!vinfo->pipe_disabled) {
			vmlfb_disable_pipe(vinfo);
		}
		break;
	case FB_BLANK_POWERDOWN:
		if (!vinfo->pipe_disabled) {
			vmlfb_disable_pipe(vinfo);
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}