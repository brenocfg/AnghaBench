#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u16 ;
struct TYPE_6__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_2__ mode_info; } ;
struct radeon_crtc {int h_border; int v_border; int /*<<< orphan*/  crtc_id; } ;
struct drm_display_mode {int crtc_hdisplay; int crtc_hblank_end; int crtc_vdisplay; int crtc_vblank_end; int crtc_hsync_start; int crtc_hsync_end; int crtc_vsync_start; int crtc_vsync_end; int flags; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_5__ {void* usAccess; } ;
struct TYPE_7__ {int ucH_Border; int ucV_Border; int /*<<< orphan*/  ucCRTC; TYPE_1__ susModeMiscInfo; void* usV_SyncWidth; void* usV_SyncOffset; void* usH_SyncWidth; void* usH_SyncOffset; void* usV_Blanking_Time; void* usV_Size; void* usH_Blanking_Time; void* usH_Size; } ;
typedef  TYPE_3__ SET_CRTC_USING_DTD_TIMING_PARAMETERS ;

/* Variables and functions */
 int ATOM_COMPOSITESYNC ; 
 int ATOM_DOUBLE_CLOCK_MODE ; 
 int ATOM_HSYNC_POLARITY ; 
 int ATOM_H_REPLICATIONBY2 ; 
 int ATOM_INTERLACE ; 
 int ATOM_VSYNC_POLARITY ; 
 int ATOM_V_REPLICATIONBY2 ; 
 int /*<<< orphan*/  COMMAND ; 
 int DRM_MODE_FLAG_CSYNC ; 
 int DRM_MODE_FLAG_DBLCLK ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCRTC_UsingDTDTiming ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void
atombios_set_crtc_dtd_timing(struct drm_crtc *crtc,
			     struct drm_display_mode *mode)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	SET_CRTC_USING_DTD_TIMING_PARAMETERS args;
	int index = GetIndexIntoMasterTable(COMMAND, SetCRTC_UsingDTDTiming);
	u16 misc = 0;

	memset(&args, 0, sizeof(args));
	args.usH_Size = cpu_to_le16(mode->crtc_hdisplay - (radeon_crtc->h_border * 2));
	args.usH_Blanking_Time =
		cpu_to_le16(mode->crtc_hblank_end - mode->crtc_hdisplay + (radeon_crtc->h_border * 2));
	args.usV_Size = cpu_to_le16(mode->crtc_vdisplay - (radeon_crtc->v_border * 2));
	args.usV_Blanking_Time =
		cpu_to_le16(mode->crtc_vblank_end - mode->crtc_vdisplay + (radeon_crtc->v_border * 2));
	args.usH_SyncOffset =
		cpu_to_le16(mode->crtc_hsync_start - mode->crtc_hdisplay + radeon_crtc->h_border);
	args.usH_SyncWidth =
		cpu_to_le16(mode->crtc_hsync_end - mode->crtc_hsync_start);
	args.usV_SyncOffset =
		cpu_to_le16(mode->crtc_vsync_start - mode->crtc_vdisplay + radeon_crtc->v_border);
	args.usV_SyncWidth =
		cpu_to_le16(mode->crtc_vsync_end - mode->crtc_vsync_start);
	args.ucH_Border = radeon_crtc->h_border;
	args.ucV_Border = radeon_crtc->v_border;

	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		misc |= ATOM_VSYNC_POLARITY;
	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		misc |= ATOM_HSYNC_POLARITY;
	if (mode->flags & DRM_MODE_FLAG_CSYNC)
		misc |= ATOM_COMPOSITESYNC;
	if (mode->flags & DRM_MODE_FLAG_INTERLACE)
		misc |= ATOM_INTERLACE;
	if (mode->flags & DRM_MODE_FLAG_DBLCLK)
		misc |= ATOM_DOUBLE_CLOCK_MODE;
	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		misc |= ATOM_H_REPLICATIONBY2 | ATOM_V_REPLICATIONBY2;

	args.susModeMiscInfo.usAccess = cpu_to_le16(misc);
	args.ucCRTC = radeon_crtc->crtc_id;

	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
}