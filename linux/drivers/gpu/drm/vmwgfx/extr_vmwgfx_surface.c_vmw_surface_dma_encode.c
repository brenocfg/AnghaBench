#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct vmw_surface_offset {int /*<<< orphan*/  mip; int /*<<< orphan*/  face; scalar_t__ bo_offset; } ;
struct TYPE_14__ {scalar_t__ reserved; scalar_t__ unsynchronized; scalar_t__ discard; } ;
struct TYPE_17__ {int suffixSize; TYPE_4__ flags; int /*<<< orphan*/  maximumOffset; } ;
struct TYPE_16__ {int /*<<< orphan*/  d; int /*<<< orphan*/  h; int /*<<< orphan*/  w; scalar_t__ srcz; scalar_t__ srcy; scalar_t__ srcx; scalar_t__ z; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_15__ {int /*<<< orphan*/  offset; } ;
struct TYPE_13__ {int /*<<< orphan*/  pitch; TYPE_5__ ptr; } ;
struct TYPE_12__ {int /*<<< orphan*/  mipmap; int /*<<< orphan*/  face; int /*<<< orphan*/  sid; } ;
struct TYPE_18__ {TYPE_3__ guest; int /*<<< orphan*/  transfer; TYPE_2__ host; } ;
struct TYPE_19__ {int size; int /*<<< orphan*/  id; } ;
struct vmw_surface_dma {TYPE_7__ suffix; TYPE_6__ cb; TYPE_8__ body; TYPE_9__ header; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
struct vmw_surface {size_t num_sizes; TYPE_1__ res; struct drm_vmw_size* sizes; struct vmw_surface_offset* offsets; int /*<<< orphan*/  format; } ;
struct svga3d_surface_desc {int dummy; } ;
struct drm_vmw_size {int /*<<< orphan*/  depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_5__ SVGAGuestPtr ;
typedef  TYPE_6__ SVGA3dCopyBox ;
typedef  TYPE_7__ SVGA3dCmdSurfaceDMASuffix ;
typedef  TYPE_8__ SVGA3dCmdSurfaceDMA ;
typedef  TYPE_9__ SVGA3dCmdHeader ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA3D_READ_HOST_VRAM ; 
 int /*<<< orphan*/  SVGA3D_WRITE_HOST_VRAM ; 
 int /*<<< orphan*/  SVGA_3D_CMD_SURFACE_DMA ; 
 int /*<<< orphan*/  svga3dsurface_calculate_pitch (struct svga3d_surface_desc const*,struct drm_vmw_size const*) ; 
 struct svga3d_surface_desc* svga3dsurface_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svga3dsurface_get_image_buffer_size (struct svga3d_surface_desc const*,struct drm_vmw_size const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmw_surface_dma_encode(struct vmw_surface *srf,
				   void *cmd_space,
				   const SVGAGuestPtr *ptr,
				   bool to_surface)
{
	uint32_t i;
	struct vmw_surface_dma *cmd = (struct vmw_surface_dma *)cmd_space;
	const struct svga3d_surface_desc *desc =
		svga3dsurface_get_desc(srf->format);

	for (i = 0; i < srf->num_sizes; ++i) {
		SVGA3dCmdHeader *header = &cmd->header;
		SVGA3dCmdSurfaceDMA *body = &cmd->body;
		SVGA3dCopyBox *cb = &cmd->cb;
		SVGA3dCmdSurfaceDMASuffix *suffix = &cmd->suffix;
		const struct vmw_surface_offset *cur_offset = &srf->offsets[i];
		const struct drm_vmw_size *cur_size = &srf->sizes[i];

		header->id = SVGA_3D_CMD_SURFACE_DMA;
		header->size = sizeof(*body) + sizeof(*cb) + sizeof(*suffix);

		body->guest.ptr = *ptr;
		body->guest.ptr.offset += cur_offset->bo_offset;
		body->guest.pitch = svga3dsurface_calculate_pitch(desc,
								  cur_size);
		body->host.sid = srf->res.id;
		body->host.face = cur_offset->face;
		body->host.mipmap = cur_offset->mip;
		body->transfer = ((to_surface) ?  SVGA3D_WRITE_HOST_VRAM :
				  SVGA3D_READ_HOST_VRAM);
		cb->x = 0;
		cb->y = 0;
		cb->z = 0;
		cb->srcx = 0;
		cb->srcy = 0;
		cb->srcz = 0;
		cb->w = cur_size->width;
		cb->h = cur_size->height;
		cb->d = cur_size->depth;

		suffix->suffixSize = sizeof(*suffix);
		suffix->maximumOffset =
			svga3dsurface_get_image_buffer_size(desc, cur_size,
							    body->guest.pitch);
		suffix->flags.discard = 0;
		suffix->flags.unsynchronized = 0;
		suffix->flags.reserved = 0;
		++cmd;
	}
}