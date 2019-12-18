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
typedef  int u32 ;
struct imgu_css_stripe_params {int input_width; int input_height; int* output_width; int* output_height; int* output_offset; unsigned int processing_mode; int phase_step; int phase_init_left_y; int phase_init_left_uv; int phase_init_top_y; int phase_init_top_uv; int pad_left_y; int pad_left_uv; int pad_right_y; int pad_right_uv; int pad_top_y; int pad_top_uv; int pad_bottom_y; int pad_bottom_uv; int crop_left_y; int crop_left_uv; int start_column_y; int start_column_uv; int chunk_width; int chunk_height; int block_width; int block_height; int /*<<< orphan*/  crop_top_uv; int /*<<< orphan*/  crop_top_y; int /*<<< orphan*/  exp_shift; } ;
struct imgu_css_scaler_info {int phase_init; int pad_left; int pad_right; int crop_left; int phase_step; int /*<<< orphan*/  crop_top; int /*<<< orphan*/  exp_shift; } ;
struct imgu_css_reso {int input_width; int input_height; scalar_t__* pin_width; scalar_t__* pin_height; int chunk_width; int block_width; int chunk_height; int block_height; int /*<<< orphan*/ * pin_stride; int /*<<< orphan*/ * pin_format; int /*<<< orphan*/  input_format; } ;
struct imgu_css_pipe {TYPE_5__* queue; TYPE_1__* rect; } ;
struct imgu_css_frame_params {int width; int height; int enable; unsigned int format; unsigned int tiling; int scaled; void* crop_top; void* crop_left; int /*<<< orphan*/  stride; scalar_t__ reduce_range; scalar_t__ mirror; scalar_t__ flip; } ;
struct imgu_css {int /*<<< orphan*/  dev; struct imgu_css_pipe* pipes; } ;
struct imgu_abi_osys_config {int dummy; } ;
struct TYPE_8__ {int width; int height; } ;
struct TYPE_9__ {TYPE_3__ mpix; } ;
struct TYPE_10__ {TYPE_4__ fmt; TYPE_2__* css_fmt; int /*<<< orphan*/  width_pad; } ;
struct TYPE_7__ {int /*<<< orphan*/  frame_format; } ;
struct TYPE_6__ {int width; int height; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 unsigned int IMGU_ABI_OSYS_PINS ; 
 size_t IMGU_ABI_OSYS_PIN_OUT ; 
 size_t IMGU_ABI_OSYS_PIN_VF ; 
 int IMGU_INPUT_BLOCK_WIDTH ; 
 int IMGU_LUMA_TO_CHROMA_RATIO ; 
 int IMGU_OSYS_BLOCK_HEIGHT ; 
 int IMGU_OSYS_BLOCK_WIDTH ; 
 int /*<<< orphan*/  IMGU_OSYS_DMA_CROP_H_LIMIT ; 
 int /*<<< orphan*/  IMGU_OSYS_DMA_CROP_W_LIMIT ; 
 int IMGU_OSYS_FIR_PHASES ; 
 int IMGU_OSYS_TAPS_UV ; 
 int IMGU_OSYS_TAPS_Y ; 
 size_t IPU3_CSS_QUEUE_OUT ; 
 size_t IPU3_CSS_QUEUE_VF ; 
 size_t IPU3_CSS_RECT_GDC ; 
 int IPU3_UAPI_ISP_VEC_ELEMS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int imgu_css_osys_calc_inp_stripe_width (int,int,int,int,int,int,int) ; 
 int imgu_css_osys_calc_stripe_offset (int,int,int,int,int) ; 
 int imgu_css_osys_calc_stripe_phase_init (int,int,int,int,int) ; 
 int imgu_css_osys_out_stripe_width (int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  imgu_css_osys_set_format (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  imgu_css_scaler_calc (int,int,int,int,struct imgu_abi_osys_config*,struct imgu_css_scaler_info*,struct imgu_css_scaler_info*,int*,int*,unsigned int*) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 void* roundclosest_down (int,int /*<<< orphan*/ ) ; 
 int rounddown (int,int) ; 
 int roundup (int,int) ; 

__attribute__((used)) static int imgu_css_osys_calc_frame_and_stripe_params(
		struct imgu_css *css, unsigned int stripes,
		struct imgu_abi_osys_config *osys,
		struct imgu_css_scaler_info *scaler_luma,
		struct imgu_css_scaler_info *scaler_chroma,
		struct imgu_css_frame_params frame_params[],
		struct imgu_css_stripe_params stripe_params[],
		unsigned int pipe)
{
	struct imgu_css_reso reso;
	unsigned int output_width, pin, s;
	u32 input_width, input_height, target_width, target_height;
	unsigned int procmode = 0;
	struct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	input_width = css_pipe->rect[IPU3_CSS_RECT_GDC].width;
	input_height = css_pipe->rect[IPU3_CSS_RECT_GDC].height;
	target_width = css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.width;
	target_height = css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.height;

	/* Frame parameters */

	/* Input width for Output System is output width of DVS (with GDC) */
	reso.input_width = css_pipe->rect[IPU3_CSS_RECT_GDC].width;

	/* Input height for Output System is output height of DVS (with GDC) */
	reso.input_height = css_pipe->rect[IPU3_CSS_RECT_GDC].height;

	reso.input_format =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].css_fmt->frame_format;

	reso.pin_width[IMGU_ABI_OSYS_PIN_OUT] =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.width;
	reso.pin_height[IMGU_ABI_OSYS_PIN_OUT] =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.height;
	reso.pin_stride[IMGU_ABI_OSYS_PIN_OUT] =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].width_pad;
	reso.pin_format[IMGU_ABI_OSYS_PIN_OUT] =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].css_fmt->frame_format;

	reso.pin_width[IMGU_ABI_OSYS_PIN_VF] =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.width;
	reso.pin_height[IMGU_ABI_OSYS_PIN_VF] =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.height;
	reso.pin_stride[IMGU_ABI_OSYS_PIN_VF] =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].width_pad;
	reso.pin_format[IMGU_ABI_OSYS_PIN_VF] =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].css_fmt->frame_format;

	/* Configure the frame parameters for all output pins */

	frame_params[IMGU_ABI_OSYS_PIN_OUT].width =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.width;
	frame_params[IMGU_ABI_OSYS_PIN_OUT].height =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.height;
	frame_params[IMGU_ABI_OSYS_PIN_VF].width =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.width;
	frame_params[IMGU_ABI_OSYS_PIN_VF].height =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.height;
	frame_params[IMGU_ABI_OSYS_PIN_VF].crop_top = 0;
	frame_params[IMGU_ABI_OSYS_PIN_VF].crop_left = 0;

	for (pin = 0; pin < IMGU_ABI_OSYS_PINS; pin++) {
		int enable = 0;
		int scaled = 0;
		unsigned int format = 0;
		unsigned int tiling = 0;

		frame_params[pin].flip = 0;
		frame_params[pin].mirror = 0;
		frame_params[pin].reduce_range = 0;
		if (reso.pin_width[pin] != 0 && reso.pin_height[pin] != 0) {
			enable = 1;
			if (pin == IMGU_ABI_OSYS_PIN_OUT) {
				if (reso.input_width < reso.pin_width[pin] ||
				    reso.input_height < reso.pin_height[pin])
					return -EINVAL;
				/*
				 * When input and output resolution is
				 * different instead of scaling, cropping
				 * should happen. Determine the crop factor
				 * to do the symmetric cropping
				 */
				frame_params[pin].crop_left = roundclosest_down(
						(reso.input_width -
						 reso.pin_width[pin]) / 2,
						 IMGU_OSYS_DMA_CROP_W_LIMIT);
				frame_params[pin].crop_top = roundclosest_down(
						(reso.input_height -
						 reso.pin_height[pin]) / 2,
						 IMGU_OSYS_DMA_CROP_H_LIMIT);
			} else {
				if (reso.pin_width[pin] != reso.input_width ||
				    reso.pin_height[pin] != reso.input_height) {
					/*
					 * If resolution is different at input
					 * and output of OSYS, scaling is
					 * considered except when pin is MAIN.
					 * Later it will be decide whether
					 * scaler factor is 1 or other
					 * and cropping has to be done or not.
					 */
					scaled = 1;
				}
			}
			imgu_css_osys_set_format(reso.pin_format[pin], &format,
						 &tiling);
		} else {
			enable = 0;
		}
		frame_params[pin].enable = enable;
		frame_params[pin].format = format;
		frame_params[pin].tiling = tiling;
		frame_params[pin].stride = reso.pin_stride[pin];
		frame_params[pin].scaled = scaled;
	}

	imgu_css_scaler_calc(input_width, input_height, target_width,
			     target_height, osys, scaler_luma, scaler_chroma,
			     &reso.pin_width[IMGU_ABI_OSYS_PIN_VF],
			     &reso.pin_height[IMGU_ABI_OSYS_PIN_VF], &procmode);
	dev_dbg(css->dev, "osys scaler procmode is %u", procmode);
	output_width = reso.pin_width[IMGU_ABI_OSYS_PIN_VF];

	if (output_width < reso.input_width / 2) {
		/* Scaling factor <= 0.5 */
		reso.chunk_width = IMGU_OSYS_BLOCK_WIDTH;
		reso.block_width = IMGU_OSYS_BLOCK_WIDTH;
	} else { /* 0.5 <= Scaling factor <= 1.0 */
		reso.chunk_width = IMGU_OSYS_BLOCK_WIDTH / 2;
		reso.block_width = IMGU_OSYS_BLOCK_WIDTH;
	}

	if (output_width <= reso.input_width * 7 / 8) {
		/* Scaling factor <= 0.875 */
		reso.chunk_height = IMGU_OSYS_BLOCK_HEIGHT;
		reso.block_height = IMGU_OSYS_BLOCK_HEIGHT;
	} else { /* 1.0 <= Scaling factor <= 1.75 */
		reso.chunk_height = IMGU_OSYS_BLOCK_HEIGHT / 2;
		reso.block_height = IMGU_OSYS_BLOCK_HEIGHT;
	}

	/*
	 * Calculate scaler configuration parameters based on input and output
	 * resolution.
	 */

	if (frame_params[IMGU_ABI_OSYS_PIN_VF].enable) {
		/*
		 * When aspect ratio is different between target resolution and
		 * required resolution, determine the crop factor to do
		 * symmetric cropping
		 */
		u32 w = reso.pin_width[IMGU_ABI_OSYS_PIN_VF] -
			frame_params[IMGU_ABI_OSYS_PIN_VF].width;
		u32 h = reso.pin_height[IMGU_ABI_OSYS_PIN_VF] -
			frame_params[IMGU_ABI_OSYS_PIN_VF].height;

		frame_params[IMGU_ABI_OSYS_PIN_VF].crop_left =
			roundclosest_down(w / 2, IMGU_OSYS_DMA_CROP_W_LIMIT);
		frame_params[IMGU_ABI_OSYS_PIN_VF].crop_top =
			roundclosest_down(h / 2, IMGU_OSYS_DMA_CROP_H_LIMIT);

		if (reso.input_height % 4 || reso.input_width % 8) {
			dev_err(css->dev, "OSYS input width is not multiple of 8 or\n");
			dev_err(css->dev, "height is not multiple of 4\n");
			return -EINVAL;
		}
	}

	/* Stripe parameters */

	if (frame_params[IMGU_ABI_OSYS_PIN_VF].enable) {
		output_width = reso.pin_width[IMGU_ABI_OSYS_PIN_VF];
	} else {
		/*
		 * in case scaler output is not enabled
		 * take output width as input width since
		 * there is no scaling at main pin.
		 * Due to the fact that main pin can be different
		 * from input resolution to osys in the case of cropping,
		 * main pin resolution is not taken.
		 */
		output_width = reso.input_width;
	}

	for (s = 0; s < stripes; s++) {
		int stripe_offset_inp_y = 0;
		int stripe_offset_inp_uv = 0;
		int stripe_offset_out_y = 0;
		int stripe_offset_out_uv = 0;
		int stripe_phase_init_y = scaler_luma->phase_init;
		int stripe_phase_init_uv = scaler_chroma->phase_init;
		int stripe_offset_blk_y = 0;
		int stripe_offset_blk_uv = 0;
		int stripe_offset_col_y = 0;
		int stripe_offset_col_uv = 0;
		int stripe_pad_left_y = scaler_luma->pad_left;
		int stripe_pad_left_uv = scaler_chroma->pad_left;
		int stripe_pad_right_y = scaler_luma->pad_right;
		int stripe_pad_right_uv = scaler_chroma->pad_right;
		int stripe_crop_left_y = scaler_luma->crop_left;
		int stripe_crop_left_uv = scaler_chroma->crop_left;
		int stripe_input_width_y = reso.input_width;
		int stripe_input_width_uv = 0;
		int stripe_output_width_y = output_width;
		int stripe_output_width_uv = 0;
		int chunk_floor_y = 0;
		int chunk_floor_uv = 0;
		int chunk_ceil_uv = 0;

		if (stripes > 1) {
			if (s > 0) {
				/* Calculate stripe offsets */
				stripe_offset_out_y =
					output_width * s / stripes;
				stripe_offset_out_y =
					rounddown(stripe_offset_out_y,
						  IPU3_UAPI_ISP_VEC_ELEMS);
				stripe_offset_out_uv = stripe_offset_out_y /
						IMGU_LUMA_TO_CHROMA_RATIO;
				stripe_offset_inp_y =
					imgu_css_osys_calc_stripe_offset(
						stripe_offset_out_y,
						IMGU_OSYS_FIR_PHASES,
						scaler_luma->phase_init,
						scaler_luma->phase_step,
						scaler_luma->pad_left);
				stripe_offset_inp_uv =
					imgu_css_osys_calc_stripe_offset(
						stripe_offset_out_uv,
						IMGU_OSYS_FIR_PHASES,
						scaler_chroma->phase_init,
						scaler_chroma->phase_step,
						scaler_chroma->pad_left);

				/* Calculate stripe phase init */
				stripe_phase_init_y =
					imgu_css_osys_calc_stripe_phase_init(
						stripe_offset_out_y,
						IMGU_OSYS_FIR_PHASES,
						scaler_luma->phase_init,
						scaler_luma->phase_step,
						scaler_luma->pad_left);
				stripe_phase_init_uv =
					imgu_css_osys_calc_stripe_phase_init(
						stripe_offset_out_uv,
						IMGU_OSYS_FIR_PHASES,
						scaler_chroma->phase_init,
						scaler_chroma->phase_step,
						scaler_chroma->pad_left);

				/*
				 * Chunk boundary corner case - luma and chroma
				 * start from different input chunks.
				 */
				chunk_floor_y = rounddown(stripe_offset_inp_y,
							  reso.chunk_width);
				chunk_floor_uv =
					rounddown(stripe_offset_inp_uv,
						  reso.chunk_width /
						  IMGU_LUMA_TO_CHROMA_RATIO);

				if (chunk_floor_y != chunk_floor_uv *
				    IMGU_LUMA_TO_CHROMA_RATIO) {
					/*
					 * Match starting luma/chroma chunks.
					 * Decrease offset for UV and add output
					 * cropping.
					 */
					stripe_offset_inp_uv -= 1;
					stripe_crop_left_uv += 1;
					stripe_phase_init_uv -=
						scaler_luma->phase_step;
					if (stripe_phase_init_uv < 0)
						stripe_phase_init_uv =
							stripe_phase_init_uv +
							IMGU_OSYS_FIR_PHASES;
				}
				/*
				 * FW workaround for a HW bug: if the first
				 * chroma pixel is generated exactly at the end
				 * of chunck scaler HW may not output the pixel
				 * for downscale factors smaller than 1.5
				 * (timing issue).
				 */
				chunk_ceil_uv =
					roundup(stripe_offset_inp_uv,
						reso.chunk_width /
						IMGU_LUMA_TO_CHROMA_RATIO);

				if (stripe_offset_inp_uv ==
				    chunk_ceil_uv - IMGU_OSYS_TAPS_UV) {
					/*
					 * Decrease input offset and add
					 * output cropping
					 */
					stripe_offset_inp_uv -= 1;
					stripe_phase_init_uv -=
						scaler_luma->phase_step;
					if (stripe_phase_init_uv < 0) {
						stripe_phase_init_uv +=
							IMGU_OSYS_FIR_PHASES;
						stripe_crop_left_uv += 1;
					}
				}

				/*
				 * Calculate block and column offsets for the
				 * input stripe
				 */
				stripe_offset_blk_y =
					rounddown(stripe_offset_inp_y,
						  IMGU_INPUT_BLOCK_WIDTH);
				stripe_offset_blk_uv =
					rounddown(stripe_offset_inp_uv,
						  IMGU_INPUT_BLOCK_WIDTH /
						  IMGU_LUMA_TO_CHROMA_RATIO);
				stripe_offset_col_y = stripe_offset_inp_y -
							stripe_offset_blk_y;
				stripe_offset_col_uv = stripe_offset_inp_uv -
							stripe_offset_blk_uv;

				/* Left padding is only for the first stripe */
				stripe_pad_left_y = 0;
				stripe_pad_left_uv = 0;
			}

			/* Right padding is only for the last stripe */
			if (s < stripes - 1) {
				int next_offset;

				stripe_pad_right_y = 0;
				stripe_pad_right_uv = 0;

				next_offset = output_width * (s + 1) / stripes;
				next_offset = rounddown(next_offset, 64);
				stripe_output_width_y = next_offset -
							stripe_offset_out_y;
			} else {
				stripe_output_width_y = output_width -
							stripe_offset_out_y;
			}

			/* Calculate target output stripe width */
			stripe_output_width_uv = stripe_output_width_y /
						IMGU_LUMA_TO_CHROMA_RATIO;
			/* Calculate input stripe width */
			stripe_input_width_y = stripe_offset_col_y +
				imgu_css_osys_calc_inp_stripe_width(
						stripe_output_width_y,
						IMGU_OSYS_FIR_PHASES,
						stripe_phase_init_y,
						scaler_luma->phase_step,
						IMGU_OSYS_TAPS_Y,
						stripe_pad_left_y,
						stripe_pad_right_y);

			stripe_input_width_uv = stripe_offset_col_uv +
				imgu_css_osys_calc_inp_stripe_width(
						stripe_output_width_uv,
						IMGU_OSYS_FIR_PHASES,
						stripe_phase_init_uv,
						scaler_chroma->phase_step,
						IMGU_OSYS_TAPS_UV,
						stripe_pad_left_uv,
						stripe_pad_right_uv);

			stripe_input_width_uv = max(DIV_ROUND_UP(
						    stripe_input_width_y,
						    IMGU_LUMA_TO_CHROMA_RATIO),
						    stripe_input_width_uv);

			stripe_input_width_y = stripe_input_width_uv *
						IMGU_LUMA_TO_CHROMA_RATIO;

			if (s >= stripes - 1) {
				stripe_input_width_y = reso.input_width -
					stripe_offset_blk_y;
				/*
				 * The scaler requires that the last stripe
				 * spans at least two input blocks.
				 */
			}

			/*
			 * Spec: input stripe width must be a multiple of 8.
			 * Increase the input width and recalculate the output
			 * width. This may produce an extra column of junk
			 * blocks which will be overwritten by the
			 * next stripe.
			 */
			stripe_input_width_y = ALIGN(stripe_input_width_y, 8);
			stripe_output_width_y =
				imgu_css_osys_out_stripe_width(
						stripe_input_width_y,
						IMGU_OSYS_FIR_PHASES,
						stripe_phase_init_y,
						scaler_luma->phase_step,
						IMGU_OSYS_TAPS_Y,
						stripe_pad_left_y,
						stripe_pad_right_y,
						stripe_offset_col_y);

			stripe_output_width_y =
					rounddown(stripe_output_width_y,
						  IMGU_LUMA_TO_CHROMA_RATIO);
		}
		/*
		 * Following section executes and process parameters
		 * for both cases - Striping or No Striping.
		 */
		{
			unsigned int i;
			int pin_scale = 0;
			/*Input resolution */

			stripe_params[s].input_width = stripe_input_width_y;
			stripe_params[s].input_height = reso.input_height;

			for (i = 0; i < IMGU_ABI_OSYS_PINS; i++) {
				if (frame_params[i].scaled) {
					/*
					 * Output stripe resolution and offset
					 * as produced by the scaler; actual
					 * output resolution may be slightly
					 * smaller.
					 */
					stripe_params[s].output_width[i] =
						stripe_output_width_y;
					stripe_params[s].output_height[i] =
						reso.pin_height[i];
					stripe_params[s].output_offset[i] =
						stripe_offset_out_y;

					pin_scale += frame_params[i].scaled;
				} else {
					/* Unscaled pin */
					stripe_params[s].output_width[i] =
						stripe_params[s].input_width;
					stripe_params[s].output_height[i] =
						stripe_params[s].input_height;
					stripe_params[s].output_offset[i] =
						stripe_offset_blk_y;
				}
			}

			/* If no pin use scale, we use BYPASS mode */
			stripe_params[s].processing_mode = procmode;
			stripe_params[s].phase_step = scaler_luma->phase_step;
			stripe_params[s].exp_shift = scaler_luma->exp_shift;
			stripe_params[s].phase_init_left_y =
				stripe_phase_init_y;
			stripe_params[s].phase_init_left_uv =
				stripe_phase_init_uv;
			stripe_params[s].phase_init_top_y =
				scaler_luma->phase_init;
			stripe_params[s].phase_init_top_uv =
				scaler_chroma->phase_init;
			stripe_params[s].pad_left_y = stripe_pad_left_y;
			stripe_params[s].pad_left_uv = stripe_pad_left_uv;
			stripe_params[s].pad_right_y = stripe_pad_right_y;
			stripe_params[s].pad_right_uv = stripe_pad_right_uv;
			stripe_params[s].pad_top_y = scaler_luma->pad_left;
			stripe_params[s].pad_top_uv = scaler_chroma->pad_left;
			stripe_params[s].pad_bottom_y = scaler_luma->pad_right;
			stripe_params[s].pad_bottom_uv =
				scaler_chroma->pad_right;
			stripe_params[s].crop_left_y = stripe_crop_left_y;
			stripe_params[s].crop_top_y = scaler_luma->crop_top;
			stripe_params[s].crop_left_uv = stripe_crop_left_uv;
			stripe_params[s].crop_top_uv = scaler_chroma->crop_top;
			stripe_params[s].start_column_y = stripe_offset_col_y;
			stripe_params[s].start_column_uv = stripe_offset_col_uv;
			stripe_params[s].chunk_width = reso.chunk_width;
			stripe_params[s].chunk_height = reso.chunk_height;
			stripe_params[s].block_width = reso.block_width;
			stripe_params[s].block_height = reso.block_height;
		}
	}

	return 0;
}