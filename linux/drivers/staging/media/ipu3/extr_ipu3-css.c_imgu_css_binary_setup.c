#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int block_width; int output_block_height; } ;
struct TYPE_12__ {TYPE_2__** params; } ;
struct TYPE_15__ {TYPE_5__ block; TYPE_3__ mem_initializers; } ;
struct TYPE_16__ {TYPE_6__ sp; } ;
struct TYPE_17__ {TYPE_7__ isp; } ;
struct imgu_fw_info {TYPE_8__ info; } ;
struct imgu_device {int dummy; } ;
struct imgu_css_pipe {size_t bindex; TYPE_9__* aux_frames; TYPE_4__* rect; int /*<<< orphan*/ ** binary_params_cs; } ;
struct imgu_css {int /*<<< orphan*/  dev; TYPE_1__* fwp; struct imgu_css_pipe* pipes; } ;
struct TYPE_18__ {int bytesperpixel; unsigned int width; int height; unsigned int bytesperline; int /*<<< orphan*/ * mem; } ;
struct TYPE_13__ {unsigned int width; unsigned int height; } ;
struct TYPE_11__ {int size; } ;
struct TYPE_10__ {struct imgu_fw_info* binary_header; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 int ENOMEM ; 
 int IMGU_ABI_NUM_MEMORIES ; 
 int IMGU_ABI_PARAM_CLASS_CONFIG ; 
 int IMGU_ABI_PARAM_CLASS_NUM ; 
 int IMGU_DVS_BLOCK_H ; 
 int IMGU_GDC_BUF_X ; 
 int IMGU_GDC_BUF_Y ; 
 int IPU3_CSS_AUX_FRAMES ; 
 size_t IPU3_CSS_AUX_FRAME_REF ; 
 size_t IPU3_CSS_AUX_FRAME_TNR ; 
 size_t IPU3_CSS_RECT_BDS ; 
 size_t IPU3_CSS_RECT_GDC ; 
 int IPU3_UAPI_ISP_VEC_ELEMS ; 
 struct imgu_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_css_binary_cleanup (struct imgu_css*,unsigned int) ; 
 scalar_t__ imgu_css_dma_buffer_resize (struct imgu_device*,int /*<<< orphan*/ *,int) ; 
 void* roundup (unsigned int,int) ; 

__attribute__((used)) static int imgu_css_binary_setup(struct imgu_css *css, unsigned int pipe)
{
	struct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	struct imgu_fw_info *bi = &css->fwp->binary_header[css_pipe->bindex];
	struct imgu_device *imgu = dev_get_drvdata(css->dev);
	int i, j, size;
	static const int BYPC = 2;	/* Bytes per component */
	unsigned int w, h;

	/* Allocate parameter memory blocks for this binary */

	for (j = IMGU_ABI_PARAM_CLASS_CONFIG; j < IMGU_ABI_PARAM_CLASS_NUM; j++)
		for (i = 0; i < IMGU_ABI_NUM_MEMORIES; i++) {
			if (imgu_css_dma_buffer_resize(
			    imgu,
			    &css_pipe->binary_params_cs[j - 1][i],
			    bi->info.isp.sp.mem_initializers.params[j][i].size))
				goto out_of_memory;
		}

	/* Allocate internal frame buffers */

	/* Reference frames for DVS, FRAME_FORMAT_YUV420_16 */
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].bytesperpixel = BYPC;
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].width =
					css_pipe->rect[IPU3_CSS_RECT_BDS].width;
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].height =
				ALIGN(css_pipe->rect[IPU3_CSS_RECT_BDS].height,
				      IMGU_DVS_BLOCK_H) + 2 * IMGU_GDC_BUF_Y;
	h = css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].height;
	w = ALIGN(css_pipe->rect[IPU3_CSS_RECT_BDS].width,
		  2 * IPU3_UAPI_ISP_VEC_ELEMS) + 2 * IMGU_GDC_BUF_X;
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].bytesperline =
		css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].bytesperpixel * w;
	size = w * h * BYPC + (w / 2) * (h / 2) * BYPC * 2;
	for (i = 0; i < IPU3_CSS_AUX_FRAMES; i++)
		if (imgu_css_dma_buffer_resize(
			imgu,
			&css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].mem[i],
			size))
			goto out_of_memory;

	/* TNR frames for temporal noise reduction, FRAME_FORMAT_YUV_LINE */
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].bytesperpixel = 1;
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].width =
			roundup(css_pipe->rect[IPU3_CSS_RECT_GDC].width,
				bi->info.isp.sp.block.block_width *
				IPU3_UAPI_ISP_VEC_ELEMS);
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].height =
			roundup(css_pipe->rect[IPU3_CSS_RECT_GDC].height,
				bi->info.isp.sp.block.output_block_height);

	w = css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].width;
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].bytesperline = w;
	h = css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].height;
	size = w * ALIGN(h * 3 / 2 + 3, 2);	/* +3 for vf_pp prefetch */
	for (i = 0; i < IPU3_CSS_AUX_FRAMES; i++)
		if (imgu_css_dma_buffer_resize(
			imgu,
			&css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].mem[i],
			size))
			goto out_of_memory;

	return 0;

out_of_memory:
	imgu_css_binary_cleanup(css, pipe);
	return -ENOMEM;
}