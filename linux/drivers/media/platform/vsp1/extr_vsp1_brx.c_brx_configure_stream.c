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
typedef  int u32 ;
struct vsp1_pipeline {TYPE_2__* output; } ;
struct vsp1_entity {scalar_t__ type; int /*<<< orphan*/  subdev; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;
struct TYPE_12__ {unsigned int source_pad; int /*<<< orphan*/  config; } ;
struct vsp1_brx {int bgcolor; TYPE_5__* inputs; TYPE_6__ entity; } ;
struct v4l2_mbus_framefmt {int width; int height; } ;
struct TYPE_11__ {TYPE_4__* rpf; } ;
struct TYPE_9__ {unsigned int flags; } ;
struct TYPE_10__ {TYPE_3__ format; } ;
struct TYPE_7__ {unsigned int flags; } ;
struct TYPE_8__ {TYPE_1__ format; } ;

/* Variables and functions */
 unsigned int V4L2_PIX_FMT_FLAG_PREMUL_ALPHA ; 
 int /*<<< orphan*/  VI6_BRU_BLD (unsigned int) ; 
 int VI6_BRU_BLD_ACMDX_255_SRC_A ; 
 int VI6_BRU_BLD_ACMDY_COEFY ; 
 int VI6_BRU_BLD_CCMDX_255_SRC_A ; 
 int VI6_BRU_BLD_CCMDY_COEFY ; 
 int VI6_BRU_BLD_CCMDY_SRC_A ; 
 int VI6_BRU_BLD_COEFY_SHIFT ; 
 int /*<<< orphan*/  VI6_BRU_CTRL (unsigned int) ; 
 int VI6_BRU_CTRL_AROP (int /*<<< orphan*/ ) ; 
 int VI6_BRU_CTRL_CROP (int /*<<< orphan*/ ) ; 
 int VI6_BRU_CTRL_DSTSEL_VRPF ; 
 int VI6_BRU_CTRL_RBC ; 
 int VI6_BRU_CTRL_SRCSEL_BRUIN (unsigned int) ; 
 int /*<<< orphan*/  VI6_BRU_INCTRL ; 
 int VI6_BRU_INCTRL_NRM ; 
 int /*<<< orphan*/  VI6_BRU_ROP ; 
 int VI6_BRU_ROP_AROP (int /*<<< orphan*/ ) ; 
 int VI6_BRU_ROP_CROP (int /*<<< orphan*/ ) ; 
 int VI6_BRU_ROP_DSTSEL_BRUIN (int) ; 
 int /*<<< orphan*/  VI6_BRU_VIRRPF_COL ; 
 int VI6_BRU_VIRRPF_COL_A_SHIFT ; 
 int /*<<< orphan*/  VI6_BRU_VIRRPF_LOC ; 
 int /*<<< orphan*/  VI6_BRU_VIRRPF_SIZE ; 
 int VI6_BRU_VIRRPF_SIZE_HSIZE_SHIFT ; 
 int VI6_BRU_VIRRPF_SIZE_VSIZE_SHIFT ; 
 int /*<<< orphan*/  VI6_ROP_NOP ; 
 scalar_t__ VSP1_ENTITY_BRU ; 
 struct vsp1_brx* to_brx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_brx_write (struct vsp1_brx*,struct vsp1_dl_body*,int /*<<< orphan*/ ,int) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_6__*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void brx_configure_stream(struct vsp1_entity *entity,
				 struct vsp1_pipeline *pipe,
				 struct vsp1_dl_list *dl,
				 struct vsp1_dl_body *dlb)
{
	struct vsp1_brx *brx = to_brx(&entity->subdev);
	struct v4l2_mbus_framefmt *format;
	unsigned int flags;
	unsigned int i;

	format = vsp1_entity_get_pad_format(&brx->entity, brx->entity.config,
					    brx->entity.source_pad);

	/*
	 * The hardware is extremely flexible but we have no userspace API to
	 * expose all the parameters, nor is it clear whether we would have use
	 * cases for all the supported modes. Let's just hardcode the parameters
	 * to sane default values for now.
	 */

	/*
	 * Disable dithering and enable color data normalization unless the
	 * format at the pipeline output is premultiplied.
	 */
	flags = pipe->output ? pipe->output->format.flags : 0;
	vsp1_brx_write(brx, dlb, VI6_BRU_INCTRL,
		       flags & V4L2_PIX_FMT_FLAG_PREMUL_ALPHA ?
		       0 : VI6_BRU_INCTRL_NRM);

	/*
	 * Set the background position to cover the whole output image and
	 * configure its color.
	 */
	vsp1_brx_write(brx, dlb, VI6_BRU_VIRRPF_SIZE,
		       (format->width << VI6_BRU_VIRRPF_SIZE_HSIZE_SHIFT) |
		       (format->height << VI6_BRU_VIRRPF_SIZE_VSIZE_SHIFT));
	vsp1_brx_write(brx, dlb, VI6_BRU_VIRRPF_LOC, 0);

	vsp1_brx_write(brx, dlb, VI6_BRU_VIRRPF_COL, brx->bgcolor |
		       (0xff << VI6_BRU_VIRRPF_COL_A_SHIFT));

	/*
	 * Route BRU input 1 as SRC input to the ROP unit and configure the ROP
	 * unit with a NOP operation to make BRU input 1 available as the
	 * Blend/ROP unit B SRC input. Only needed for BRU, the BRS has no ROP
	 * unit.
	 */
	if (entity->type == VSP1_ENTITY_BRU)
		vsp1_brx_write(brx, dlb, VI6_BRU_ROP,
			       VI6_BRU_ROP_DSTSEL_BRUIN(1) |
			       VI6_BRU_ROP_CROP(VI6_ROP_NOP) |
			       VI6_BRU_ROP_AROP(VI6_ROP_NOP));

	for (i = 0; i < brx->entity.source_pad; ++i) {
		bool premultiplied = false;
		u32 ctrl = 0;

		/*
		 * Configure all Blend/ROP units corresponding to an enabled BRx
		 * input for alpha blending. Blend/ROP units corresponding to
		 * disabled BRx inputs are used in ROP NOP mode to ignore the
		 * SRC input.
		 */
		if (brx->inputs[i].rpf) {
			ctrl |= VI6_BRU_CTRL_RBC;

			premultiplied = brx->inputs[i].rpf->format.flags
				      & V4L2_PIX_FMT_FLAG_PREMUL_ALPHA;
		} else {
			ctrl |= VI6_BRU_CTRL_CROP(VI6_ROP_NOP)
			     |  VI6_BRU_CTRL_AROP(VI6_ROP_NOP);
		}

		/*
		 * Select the virtual RPF as the Blend/ROP unit A DST input to
		 * serve as a background color.
		 */
		if (i == 0)
			ctrl |= VI6_BRU_CTRL_DSTSEL_VRPF;

		/*
		 * Route inputs 0 to 3 as SRC inputs to Blend/ROP units A to D
		 * in that order. In the BRU the Blend/ROP unit B SRC is
		 * hardwired to the ROP unit output, the corresponding register
		 * bits must be set to 0. The BRS has no ROP unit and doesn't
		 * need any special processing.
		 */
		if (!(entity->type == VSP1_ENTITY_BRU && i == 1))
			ctrl |= VI6_BRU_CTRL_SRCSEL_BRUIN(i);

		vsp1_brx_write(brx, dlb, VI6_BRU_CTRL(i), ctrl);

		/*
		 * Hardcode the blending formula to
		 *
		 *	DSTc = DSTc * (1 - SRCa) + SRCc * SRCa
		 *	DSTa = DSTa * (1 - SRCa) + SRCa
		 *
		 * when the SRC input isn't premultiplied, and to
		 *
		 *	DSTc = DSTc * (1 - SRCa) + SRCc
		 *	DSTa = DSTa * (1 - SRCa) + SRCa
		 *
		 * otherwise.
		 */
		vsp1_brx_write(brx, dlb, VI6_BRU_BLD(i),
			       VI6_BRU_BLD_CCMDX_255_SRC_A |
			       (premultiplied ? VI6_BRU_BLD_CCMDY_COEFY :
						VI6_BRU_BLD_CCMDY_SRC_A) |
			       VI6_BRU_BLD_ACMDX_255_SRC_A |
			       VI6_BRU_BLD_ACMDY_COEFY |
			       (0xff << VI6_BRU_BLD_COEFY_SHIFT));
	}
}