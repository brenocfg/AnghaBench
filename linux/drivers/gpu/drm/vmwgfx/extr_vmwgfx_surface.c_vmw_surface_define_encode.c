#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {TYPE_3__* face; int /*<<< orphan*/  format; scalar_t__ surfaceFlags; int /*<<< orphan*/  sid; } ;
struct TYPE_6__ {int size; int /*<<< orphan*/  id; } ;
struct vmw_surface_define {TYPE_4__ body; TYPE_1__ header; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct vmw_surface {int num_sizes; struct drm_vmw_size* sizes; int /*<<< orphan*/ * mip_levels; int /*<<< orphan*/  format; scalar_t__ flags; TYPE_2__ res; } ;
struct drm_vmw_size {int /*<<< orphan*/  depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_10__ {int /*<<< orphan*/  depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {int /*<<< orphan*/  numMipLevels; } ;
typedef  scalar_t__ SVGA3dSurface1Flags ;
typedef  TYPE_5__ SVGA3dSize ;

/* Variables and functions */
 int DRM_VMW_MAX_SURFACE_FACES ; 
 int /*<<< orphan*/  SVGA_3D_CMD_SURFACE_DEFINE ; 

__attribute__((used)) static void vmw_surface_define_encode(const struct vmw_surface *srf,
				      void *cmd_space)
{
	struct vmw_surface_define *cmd = (struct vmw_surface_define *)
		cmd_space;
	struct drm_vmw_size *src_size;
	SVGA3dSize *cmd_size;
	uint32_t cmd_len;
	int i;

	cmd_len = sizeof(cmd->body) + srf->num_sizes * sizeof(SVGA3dSize);

	cmd->header.id = SVGA_3D_CMD_SURFACE_DEFINE;
	cmd->header.size = cmd_len;
	cmd->body.sid = srf->res.id;
	/*
	 * Downcast of surfaceFlags, was upcasted when received from user-space,
	 * since driver internally stores as 64 bit.
	 * For legacy surface define only 32 bit flag is supported.
	 */
	cmd->body.surfaceFlags = (SVGA3dSurface1Flags)srf->flags;
	cmd->body.format = srf->format;
	for (i = 0; i < DRM_VMW_MAX_SURFACE_FACES; ++i)
		cmd->body.face[i].numMipLevels = srf->mip_levels[i];

	cmd += 1;
	cmd_size = (SVGA3dSize *) cmd;
	src_size = srf->sizes;

	for (i = 0; i < srf->num_sizes; ++i, cmd_size++, src_size++) {
		cmd_size->width = src_size->width;
		cmd_size->height = src_size->height;
		cmd_size->depth = src_size->depth;
	}
}