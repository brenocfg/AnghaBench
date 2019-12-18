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
struct allegro_channel {int height; int stride; int sizeimage_raw; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  level; int /*<<< orphan*/  cpb_size; void* bitrate_peak; void* bitrate; int /*<<< orphan*/  bitrate_mode; int /*<<< orphan*/  width; int /*<<< orphan*/  sizeimage_encoded; int /*<<< orphan*/  profile; int /*<<< orphan*/  codec; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLEGRO_GOP_SIZE_DEFAULT ; 
 int ALLEGRO_HEIGHT_DEFAULT ; 
 int /*<<< orphan*/  ALLEGRO_WIDTH_DEFAULT ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_H264 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_NV12 ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 int /*<<< orphan*/  estimate_stream_size (int /*<<< orphan*/ ,int) ; 
 void* maximum_bitrate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maximum_cpb_size (int /*<<< orphan*/ ) ; 
 int round_up (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  select_minimum_h264_level (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void allegro_set_default_params(struct allegro_channel *channel)
{
	channel->width = ALLEGRO_WIDTH_DEFAULT;
	channel->height = ALLEGRO_HEIGHT_DEFAULT;
	channel->stride = round_up(channel->width, 32);

	channel->colorspace = V4L2_COLORSPACE_REC709;
	channel->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	channel->quantization = V4L2_QUANTIZATION_DEFAULT;
	channel->xfer_func = V4L2_XFER_FUNC_DEFAULT;

	channel->pixelformat = V4L2_PIX_FMT_NV12;
	channel->sizeimage_raw = channel->stride * channel->height * 3 / 2;

	channel->codec = V4L2_PIX_FMT_H264;
	channel->profile = V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE;
	channel->level =
		select_minimum_h264_level(channel->width, channel->height);
	channel->sizeimage_encoded =
		estimate_stream_size(channel->width, channel->height);

	channel->bitrate_mode = V4L2_MPEG_VIDEO_BITRATE_MODE_CBR;
	channel->bitrate = maximum_bitrate(channel->level);
	channel->bitrate_peak = maximum_bitrate(channel->level);
	channel->cpb_size = maximum_cpb_size(channel->level);
	channel->gop_size = ALLEGRO_GOP_SIZE_DEFAULT;
}