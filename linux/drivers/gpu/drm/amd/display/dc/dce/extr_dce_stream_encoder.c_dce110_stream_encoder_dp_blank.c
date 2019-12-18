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
struct stream_encoder {int dummy; } ;
struct dce110_stream_encoder {int dummy; } ;

/* Variables and functions */
 struct dce110_stream_encoder* DCE110STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int DP_BLANK_MAX_RETRY ; 
 int /*<<< orphan*/  DP_STEER_FIFO ; 
 int /*<<< orphan*/  DP_STEER_FIFO_RESET ; 
 int /*<<< orphan*/  DP_VID_STREAM_CNTL ; 
 int /*<<< orphan*/  DP_VID_STREAM_DIS_DEFER ; 
 int /*<<< orphan*/  DP_VID_STREAM_ENABLE ; 
 int /*<<< orphan*/  DP_VID_STREAM_STATUS ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void dce110_stream_encoder_dp_blank(
	struct stream_encoder *enc)
{
	struct dce110_stream_encoder *enc110 = DCE110STRENC_FROM_STRENC(enc);
	uint32_t  reg1 = 0;
	uint32_t max_retries = DP_BLANK_MAX_RETRY * 10;

	/* Note: For CZ, we are changing driver default to disable
	 * stream deferred to next VBLANK. If results are positive, we
	 * will make the same change to all DCE versions. There are a
	 * handful of panels that cannot handle disable stream at
	 * HBLANK and will result in a white line flash across the
	 * screen on stream disable. */
	REG_GET(DP_VID_STREAM_CNTL, DP_VID_STREAM_ENABLE, &reg1);
	if ((reg1 & 0x1) == 0)
		/*stream not enabled*/
		return;
	/* Specify the video stream disable point
	 * (2 = start of the next vertical blank) */
	REG_UPDATE(DP_VID_STREAM_CNTL, DP_VID_STREAM_DIS_DEFER, 2);
	/* Larger delay to wait until VBLANK - use max retry of
	 * 10us*3000=30ms. This covers 16.6ms of typical 60 Hz mode +
	 * a little more because we may not trust delay accuracy.
	 */
	max_retries = DP_BLANK_MAX_RETRY * 150;

	/* disable DP stream */
	REG_UPDATE(DP_VID_STREAM_CNTL, DP_VID_STREAM_ENABLE, 0);

	/* the encoder stops sending the video stream
	 * at the start of the vertical blanking.
	 * Poll for DP_VID_STREAM_STATUS == 0
	 */

	REG_WAIT(DP_VID_STREAM_CNTL, DP_VID_STREAM_STATUS,
			0,
			10, max_retries);

	/* Tell the DP encoder to ignore timing from CRTC, must be done after
	 * the polling. If we set DP_STEER_FIFO_RESET before DP stream blank is
	 * complete, stream status will be stuck in video stream enabled state,
	 * i.e. DP_VID_STREAM_STATUS stuck at 1.
	 */

	REG_UPDATE(DP_STEER_FIFO, DP_STEER_FIFO_RESET, true);
}