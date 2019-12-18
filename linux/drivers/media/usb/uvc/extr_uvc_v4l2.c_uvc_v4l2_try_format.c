#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_7__ {scalar_t__ pixelformat; int width; int height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  field; } ;
struct TYPE_8__ {TYPE_3__ pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_4__ fmt; } ;
struct uvc_streaming_control {int bmHint; int /*<<< orphan*/  dwMaxVideoFrameSize; int /*<<< orphan*/  dwFrameInterval; int /*<<< orphan*/  bFrameIndex; int /*<<< orphan*/  bFormatIndex; } ;
struct TYPE_6__ {int /*<<< orphan*/  dwMaxVideoFrameSize; } ;
struct uvc_streaming {scalar_t__ type; unsigned int nformats; int /*<<< orphan*/  mutex; TYPE_2__ ctrl; TYPE_1__* dev; struct uvc_format* def_format; struct uvc_format* format; } ;
struct uvc_frame {int wWidth; int wHeight; int dwDefaultFrameInterval; int /*<<< orphan*/  bFrameIndex; } ;
struct uvc_format {scalar_t__ fcc; unsigned int nframes; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  index; struct uvc_frame* frame; } ;
struct TYPE_5__ {int quirks; } ;

/* Variables and functions */
 int EINVAL ; 
 int UVC_QUIRK_PROBE_EXTRAFIELDS ; 
 int /*<<< orphan*/  UVC_TRACE_FORMAT ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  memset (struct uvc_streaming_control*,int /*<<< orphan*/ ,int) ; 
 unsigned int min (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int uvc_probe_video (struct uvc_streaming*,struct uvc_streaming_control*) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  uvc_try_frame_interval (struct uvc_frame*,int) ; 
 int /*<<< orphan*/  uvc_v4l2_get_bytesperline (struct uvc_format*,struct uvc_frame*) ; 

__attribute__((used)) static int uvc_v4l2_try_format(struct uvc_streaming *stream,
	struct v4l2_format *fmt, struct uvc_streaming_control *probe,
	struct uvc_format **uvc_format, struct uvc_frame **uvc_frame)
{
	struct uvc_format *format = NULL;
	struct uvc_frame *frame = NULL;
	u16 rw, rh;
	unsigned int d, maxd;
	unsigned int i;
	u32 interval;
	int ret = 0;
	u8 *fcc;

	if (fmt->type != stream->type)
		return -EINVAL;

	fcc = (u8 *)&fmt->fmt.pix.pixelformat;
	uvc_trace(UVC_TRACE_FORMAT, "Trying format 0x%08x (%c%c%c%c): %ux%u.\n",
			fmt->fmt.pix.pixelformat,
			fcc[0], fcc[1], fcc[2], fcc[3],
			fmt->fmt.pix.width, fmt->fmt.pix.height);

	/* Check if the hardware supports the requested format, use the default
	 * format otherwise.
	 */
	for (i = 0; i < stream->nformats; ++i) {
		format = &stream->format[i];
		if (format->fcc == fmt->fmt.pix.pixelformat)
			break;
	}

	if (i == stream->nformats) {
		format = stream->def_format;
		fmt->fmt.pix.pixelformat = format->fcc;
	}

	/* Find the closest image size. The distance between image sizes is
	 * the size in pixels of the non-overlapping regions between the
	 * requested size and the frame-specified size.
	 */
	rw = fmt->fmt.pix.width;
	rh = fmt->fmt.pix.height;
	maxd = (unsigned int)-1;

	for (i = 0; i < format->nframes; ++i) {
		u16 w = format->frame[i].wWidth;
		u16 h = format->frame[i].wHeight;

		d = min(w, rw) * min(h, rh);
		d = w*h + rw*rh - 2*d;
		if (d < maxd) {
			maxd = d;
			frame = &format->frame[i];
		}

		if (maxd == 0)
			break;
	}

	if (frame == NULL) {
		uvc_trace(UVC_TRACE_FORMAT, "Unsupported size %ux%u.\n",
				fmt->fmt.pix.width, fmt->fmt.pix.height);
		return -EINVAL;
	}

	/* Use the default frame interval. */
	interval = frame->dwDefaultFrameInterval;
	uvc_trace(UVC_TRACE_FORMAT, "Using default frame interval %u.%u us "
		"(%u.%u fps).\n", interval/10, interval%10, 10000000/interval,
		(100000000/interval)%10);

	/* Set the format index, frame index and frame interval. */
	memset(probe, 0, sizeof(*probe));
	probe->bmHint = 1;	/* dwFrameInterval */
	probe->bFormatIndex = format->index;
	probe->bFrameIndex = frame->bFrameIndex;
	probe->dwFrameInterval = uvc_try_frame_interval(frame, interval);
	/* Some webcams stall the probe control set request when the
	 * dwMaxVideoFrameSize field is set to zero. The UVC specification
	 * clearly states that the field is read-only from the host, so this
	 * is a webcam bug. Set dwMaxVideoFrameSize to the value reported by
	 * the webcam to work around the problem.
	 *
	 * The workaround could probably be enabled for all webcams, so the
	 * quirk can be removed if needed. It's currently useful to detect
	 * webcam bugs and fix them before they hit the market (providing
	 * developers test their webcams with the Linux driver as well as with
	 * the Windows driver).
	 */
	mutex_lock(&stream->mutex);
	if (stream->dev->quirks & UVC_QUIRK_PROBE_EXTRAFIELDS)
		probe->dwMaxVideoFrameSize =
			stream->ctrl.dwMaxVideoFrameSize;

	/* Probe the device. */
	ret = uvc_probe_video(stream, probe);
	mutex_unlock(&stream->mutex);
	if (ret < 0)
		goto done;

	fmt->fmt.pix.width = frame->wWidth;
	fmt->fmt.pix.height = frame->wHeight;
	fmt->fmt.pix.field = V4L2_FIELD_NONE;
	fmt->fmt.pix.bytesperline = uvc_v4l2_get_bytesperline(format, frame);
	fmt->fmt.pix.sizeimage = probe->dwMaxVideoFrameSize;
	fmt->fmt.pix.colorspace = format->colorspace;

	if (uvc_format != NULL)
		*uvc_format = format;
	if (uvc_frame != NULL)
		*uvc_frame = frame;

done:
	return ret;
}