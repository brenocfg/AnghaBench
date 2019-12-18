#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vsp1_rwpf_memory {unsigned int* addr; } ;
struct TYPE_10__ {unsigned int active; scalar_t__ rotate; } ;
struct TYPE_12__ {int /*<<< orphan*/  config; struct vsp1_device* vsp1; } ;
struct v4l2_pix_format_mplane {unsigned int width; unsigned int height; unsigned int num_planes; TYPE_3__* plane_fmt; } ;
struct vsp1_rwpf {int writeback; TYPE_4__ flip; TYPE_6__ entity; struct vsp1_format_info* fmtinfo; struct v4l2_pix_format_mplane format; struct vsp1_rwpf_memory mem; } ;
struct vsp1_pipeline {int partitions; scalar_t__ lif; TYPE_2__* partition; } ;
struct vsp1_format_info {int hsub; int vsub; unsigned int* bpp; scalar_t__ swap_uv; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;
struct vsp1_device {TYPE_5__* info; } ;
struct v4l2_mbus_framefmt {unsigned int width; unsigned int height; } ;
struct TYPE_11__ {int gen; } ;
struct TYPE_9__ {unsigned int bytesperline; } ;
struct TYPE_7__ {unsigned int width; unsigned int left; } ;
struct TYPE_8__ {TYPE_1__ wpf; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RWPF_PAD_SINK ; 
 int /*<<< orphan*/  VI6_WPF_DSTM_ADDR_C0 ; 
 int /*<<< orphan*/  VI6_WPF_DSTM_ADDR_C1 ; 
 int /*<<< orphan*/  VI6_WPF_DSTM_ADDR_Y ; 
 int /*<<< orphan*/  VI6_WPF_HSZCLIP ; 
 unsigned int VI6_WPF_SZCLIP_EN ; 
 unsigned int VI6_WPF_SZCLIP_OFST_SHIFT ; 
 unsigned int VI6_WPF_SZCLIP_SIZE_SHIFT ; 
 int /*<<< orphan*/  VI6_WPF_VSZCLIP ; 
 int /*<<< orphan*/  WPF_CTRL_HFLIP ; 
 int /*<<< orphan*/  WPF_CTRL_VFLIP ; 
 unsigned int max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swap (unsigned int,unsigned int) ; 
 struct vsp1_rwpf* to_rwpf (int /*<<< orphan*/ *) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_wpf_write (struct vsp1_rwpf*,struct vsp1_dl_body*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void wpf_configure_partition(struct vsp1_entity *entity,
				    struct vsp1_pipeline *pipe,
				    struct vsp1_dl_list *dl,
				    struct vsp1_dl_body *dlb)
{
	struct vsp1_rwpf *wpf = to_rwpf(&entity->subdev);
	struct vsp1_device *vsp1 = wpf->entity.vsp1;
	struct vsp1_rwpf_memory mem = wpf->mem;
	const struct v4l2_mbus_framefmt *sink_format;
	const struct v4l2_pix_format_mplane *format = &wpf->format;
	const struct vsp1_format_info *fmtinfo = wpf->fmtinfo;
	unsigned int width;
	unsigned int height;
	unsigned int left;
	unsigned int offset;
	unsigned int flip;
	unsigned int i;

	sink_format = vsp1_entity_get_pad_format(&wpf->entity,
						 wpf->entity.config,
						 RWPF_PAD_SINK);
	width = sink_format->width;
	height = sink_format->height;
	left = 0;

	/*
	 * Cropping. The partition algorithm can split the image into
	 * multiple slices.
	 */
	if (pipe->partitions > 1) {
		width = pipe->partition->wpf.width;
		left = pipe->partition->wpf.left;
	}

	vsp1_wpf_write(wpf, dlb, VI6_WPF_HSZCLIP, VI6_WPF_SZCLIP_EN |
		       (0 << VI6_WPF_SZCLIP_OFST_SHIFT) |
		       (width << VI6_WPF_SZCLIP_SIZE_SHIFT));
	vsp1_wpf_write(wpf, dlb, VI6_WPF_VSZCLIP, VI6_WPF_SZCLIP_EN |
		       (0 << VI6_WPF_SZCLIP_OFST_SHIFT) |
		       (height << VI6_WPF_SZCLIP_SIZE_SHIFT));

	/*
	 * For display pipelines without writeback enabled there's no memory
	 * address to configure, return now.
	 */
	if (pipe->lif && !wpf->writeback)
		return;

	/*
	 * Update the memory offsets based on flipping configuration.
	 * The destination addresses point to the locations where the
	 * VSP starts writing to memory, which can be any corner of the
	 * image depending on the combination of flipping and rotation.
	 */

	/*
	 * First take the partition left coordinate into account.
	 * Compute the offset to order the partitions correctly on the
	 * output based on whether flipping is enabled. Consider
	 * horizontal flipping when rotation is disabled but vertical
	 * flipping when rotation is enabled, as rotating the image
	 * switches the horizontal and vertical directions. The offset
	 * is applied horizontally or vertically accordingly.
	 */
	flip = wpf->flip.active;

	if (flip & BIT(WPF_CTRL_HFLIP) && !wpf->flip.rotate)
		offset = format->width - left - width;
	else if (flip & BIT(WPF_CTRL_VFLIP) && wpf->flip.rotate)
		offset = format->height - left - width;
	else
		offset = left;

	for (i = 0; i < format->num_planes; ++i) {
		unsigned int hsub = i > 0 ? fmtinfo->hsub : 1;
		unsigned int vsub = i > 0 ? fmtinfo->vsub : 1;

		if (wpf->flip.rotate)
			mem.addr[i] += offset / vsub
				     * format->plane_fmt[i].bytesperline;
		else
			mem.addr[i] += offset / hsub
				     * fmtinfo->bpp[i] / 8;
	}

	if (flip & BIT(WPF_CTRL_VFLIP)) {
		/*
		 * When rotating the output (after rotation) image
		 * height is equal to the partition width (before
		 * rotation). Otherwise it is equal to the output
		 * image height.
		 */
		if (wpf->flip.rotate)
			height = width;
		else
			height = format->height;

		mem.addr[0] += (height - 1)
			     * format->plane_fmt[0].bytesperline;

		if (format->num_planes > 1) {
			offset = (height / fmtinfo->vsub - 1)
			       * format->plane_fmt[1].bytesperline;
			mem.addr[1] += offset;
			mem.addr[2] += offset;
		}
	}

	if (wpf->flip.rotate && !(flip & BIT(WPF_CTRL_HFLIP))) {
		unsigned int hoffset = max(0, (int)format->width - 16);

		/*
		 * Compute the output coordinate. The partition
		 * horizontal (left) offset becomes a vertical offset.
		 */
		for (i = 0; i < format->num_planes; ++i) {
			unsigned int hsub = i > 0 ? fmtinfo->hsub : 1;

			mem.addr[i] += hoffset / hsub
				     * fmtinfo->bpp[i] / 8;
		}
	}

	/*
	 * On Gen3 hardware the SPUVS bit has no effect on 3-planar
	 * formats. Swap the U and V planes manually in that case.
	 */
	if (vsp1->info->gen == 3 && format->num_planes == 3 &&
	    fmtinfo->swap_uv)
		swap(mem.addr[1], mem.addr[2]);

	vsp1_wpf_write(wpf, dlb, VI6_WPF_DSTM_ADDR_Y, mem.addr[0]);
	vsp1_wpf_write(wpf, dlb, VI6_WPF_DSTM_ADDR_C0, mem.addr[1]);
	vsp1_wpf_write(wpf, dlb, VI6_WPF_DSTM_ADDR_C1, mem.addr[2]);

	/*
	 * Writeback operates in single-shot mode and lasts for a single frame,
	 * reset the writeback flag to false for the next frame.
	 */
	wpf->writeback = false;
}