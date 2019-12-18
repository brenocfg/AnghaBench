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
struct jpeg_decode_return_params_t {scalar_t__ error_code; int /*<<< orphan*/  decode_time_in_us; } ;
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct delta_ctx {int /*<<< orphan*/  name; int /*<<< orphan*/  decode_errors; int /*<<< orphan*/  decoded_frames; int /*<<< orphan*/  stream_errors; struct delta_dev* dev; } ;

/* Variables and functions */
 scalar_t__ JPEG_DECODER_NO_ERROR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_str (scalar_t__) ; 
 scalar_t__ is_stream_error (scalar_t__) ; 

__attribute__((used)) static bool delta_mjpeg_check_status(struct delta_ctx *pctx,
				     struct jpeg_decode_return_params_t *status)
{
	struct delta_dev *delta = pctx->dev;
	bool dump = false;

	if (status->error_code == JPEG_DECODER_NO_ERROR)
		goto out;

	if (is_stream_error(status->error_code)) {
		dev_warn_ratelimited(delta->dev,
				     "%s  firmware: stream error @ frame %d (%s)\n",
				     pctx->name, pctx->decoded_frames,
				     err_str(status->error_code));
		pctx->stream_errors++;
	} else {
		dev_warn_ratelimited(delta->dev,
				     "%s  firmware: decode error @ frame %d (%s)\n",
				     pctx->name, pctx->decoded_frames,
				     err_str(status->error_code));
		pctx->decode_errors++;
		dump = true;
	}

out:
	dev_dbg(delta->dev,
		"%s  firmware: decoding time(us)=%d\n", pctx->name,
		status->decode_time_in_us);

	return dump;
}