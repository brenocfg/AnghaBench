#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct uvc_streaming_control {scalar_t__ dwMaxPayloadTransferSize; int /*<<< orphan*/  wCompWindowSize; int /*<<< orphan*/  wCompQuality; int /*<<< orphan*/  wPFrameRate; int /*<<< orphan*/  wKeyFrameRate; } ;
struct uvc_streaming {scalar_t__ maxpsize; TYPE_2__* dev; TYPE_1__* intf; } ;
struct TYPE_4__ {int quirks; } ;
struct TYPE_3__ {int num_altsetting; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  UVC_GET_CUR ; 
 int /*<<< orphan*/  UVC_GET_MAX ; 
 int /*<<< orphan*/  UVC_GET_MIN ; 
 int UVC_QUIRK_PROBE_MINMAX ; 
 int uvc_get_video_ctrl (struct uvc_streaming*,struct uvc_streaming_control*,int,int /*<<< orphan*/ ) ; 
 int uvc_set_video_ctrl (struct uvc_streaming*,struct uvc_streaming_control*,int) ; 

int uvc_probe_video(struct uvc_streaming *stream,
	struct uvc_streaming_control *probe)
{
	struct uvc_streaming_control probe_min, probe_max;
	u16 bandwidth;
	unsigned int i;
	int ret;

	/* Perform probing. The device should adjust the requested values
	 * according to its capabilities. However, some devices, namely the
	 * first generation UVC Logitech webcams, don't implement the Video
	 * Probe control properly, and just return the needed bandwidth. For
	 * that reason, if the needed bandwidth exceeds the maximum available
	 * bandwidth, try to lower the quality.
	 */
	ret = uvc_set_video_ctrl(stream, probe, 1);
	if (ret < 0)
		goto done;

	/* Get the minimum and maximum values for compression settings. */
	if (!(stream->dev->quirks & UVC_QUIRK_PROBE_MINMAX)) {
		ret = uvc_get_video_ctrl(stream, &probe_min, 1, UVC_GET_MIN);
		if (ret < 0)
			goto done;
		ret = uvc_get_video_ctrl(stream, &probe_max, 1, UVC_GET_MAX);
		if (ret < 0)
			goto done;

		probe->wCompQuality = probe_max.wCompQuality;
	}

	for (i = 0; i < 2; ++i) {
		ret = uvc_set_video_ctrl(stream, probe, 1);
		if (ret < 0)
			goto done;
		ret = uvc_get_video_ctrl(stream, probe, 1, UVC_GET_CUR);
		if (ret < 0)
			goto done;

		if (stream->intf->num_altsetting == 1)
			break;

		bandwidth = probe->dwMaxPayloadTransferSize;
		if (bandwidth <= stream->maxpsize)
			break;

		if (stream->dev->quirks & UVC_QUIRK_PROBE_MINMAX) {
			ret = -ENOSPC;
			goto done;
		}

		/* TODO: negotiate compression parameters */
		probe->wKeyFrameRate = probe_min.wKeyFrameRate;
		probe->wPFrameRate = probe_min.wPFrameRate;
		probe->wCompQuality = probe_max.wCompQuality;
		probe->wCompWindowSize = probe_min.wCompWindowSize;
	}

done:
	return ret;
}