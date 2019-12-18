#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_2__ {unsigned int decode_image_width; int /*<<< orphan*/  use_ctx_buf; } ;
struct amdgpu_device {TYPE_1__ uvd; } ;

/* Variables and functions */
 int ALIGN (unsigned int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int le32_to_cpu (unsigned int) ; 
 unsigned int max (unsigned int,unsigned int) ; 

__attribute__((used)) static int amdgpu_uvd_cs_msg_decode(struct amdgpu_device *adev, uint32_t *msg,
	unsigned buf_sizes[])
{
	unsigned stream_type = msg[4];
	unsigned width = msg[6];
	unsigned height = msg[7];
	unsigned dpb_size = msg[9];
	unsigned pitch = msg[28];
	unsigned level = msg[57];

	unsigned width_in_mb = width / 16;
	unsigned height_in_mb = ALIGN(height / 16, 2);
	unsigned fs_in_mb = width_in_mb * height_in_mb;

	unsigned image_size, tmp, min_dpb_size, num_dpb_buffer;
	unsigned min_ctx_size = ~0;

	image_size = width * height;
	image_size += image_size / 2;
	image_size = ALIGN(image_size, 1024);

	switch (stream_type) {
	case 0: /* H264 */
		switch(level) {
		case 30:
			num_dpb_buffer = 8100 / fs_in_mb;
			break;
		case 31:
			num_dpb_buffer = 18000 / fs_in_mb;
			break;
		case 32:
			num_dpb_buffer = 20480 / fs_in_mb;
			break;
		case 41:
			num_dpb_buffer = 32768 / fs_in_mb;
			break;
		case 42:
			num_dpb_buffer = 34816 / fs_in_mb;
			break;
		case 50:
			num_dpb_buffer = 110400 / fs_in_mb;
			break;
		case 51:
			num_dpb_buffer = 184320 / fs_in_mb;
			break;
		default:
			num_dpb_buffer = 184320 / fs_in_mb;
			break;
		}
		num_dpb_buffer++;
		if (num_dpb_buffer > 17)
			num_dpb_buffer = 17;

		/* reference picture buffer */
		min_dpb_size = image_size * num_dpb_buffer;

		/* macroblock context buffer */
		min_dpb_size += width_in_mb * height_in_mb * num_dpb_buffer * 192;

		/* IT surface buffer */
		min_dpb_size += width_in_mb * height_in_mb * 32;
		break;

	case 1: /* VC1 */

		/* reference picture buffer */
		min_dpb_size = image_size * 3;

		/* CONTEXT_BUFFER */
		min_dpb_size += width_in_mb * height_in_mb * 128;

		/* IT surface buffer */
		min_dpb_size += width_in_mb * 64;

		/* DB surface buffer */
		min_dpb_size += width_in_mb * 128;

		/* BP */
		tmp = max(width_in_mb, height_in_mb);
		min_dpb_size += ALIGN(tmp * 7 * 16, 64);
		break;

	case 3: /* MPEG2 */

		/* reference picture buffer */
		min_dpb_size = image_size * 3;
		break;

	case 4: /* MPEG4 */

		/* reference picture buffer */
		min_dpb_size = image_size * 3;

		/* CM */
		min_dpb_size += width_in_mb * height_in_mb * 64;

		/* IT surface buffer */
		min_dpb_size += ALIGN(width_in_mb * height_in_mb * 32, 64);
		break;

	case 7: /* H264 Perf */
		switch(level) {
		case 30:
			num_dpb_buffer = 8100 / fs_in_mb;
			break;
		case 31:
			num_dpb_buffer = 18000 / fs_in_mb;
			break;
		case 32:
			num_dpb_buffer = 20480 / fs_in_mb;
			break;
		case 41:
			num_dpb_buffer = 32768 / fs_in_mb;
			break;
		case 42:
			num_dpb_buffer = 34816 / fs_in_mb;
			break;
		case 50:
			num_dpb_buffer = 110400 / fs_in_mb;
			break;
		case 51:
			num_dpb_buffer = 184320 / fs_in_mb;
			break;
		default:
			num_dpb_buffer = 184320 / fs_in_mb;
			break;
		}
		num_dpb_buffer++;
		if (num_dpb_buffer > 17)
			num_dpb_buffer = 17;

		/* reference picture buffer */
		min_dpb_size = image_size * num_dpb_buffer;

		if (!adev->uvd.use_ctx_buf){
			/* macroblock context buffer */
			min_dpb_size +=
				width_in_mb * height_in_mb * num_dpb_buffer * 192;

			/* IT surface buffer */
			min_dpb_size += width_in_mb * height_in_mb * 32;
		} else {
			/* macroblock context buffer */
			min_ctx_size =
				width_in_mb * height_in_mb * num_dpb_buffer * 192;
		}
		break;

	case 8: /* MJPEG */
		min_dpb_size = 0;
		break;

	case 16: /* H265 */
		image_size = (ALIGN(width, 16) * ALIGN(height, 16) * 3) / 2;
		image_size = ALIGN(image_size, 256);

		num_dpb_buffer = (le32_to_cpu(msg[59]) & 0xff) + 2;
		min_dpb_size = image_size * num_dpb_buffer;
		min_ctx_size = ((width + 255) / 16) * ((height + 255) / 16)
					   * 16 * num_dpb_buffer + 52 * 1024;
		break;

	default:
		DRM_ERROR("UVD codec not handled %d!\n", stream_type);
		return -EINVAL;
	}

	if (width > pitch) {
		DRM_ERROR("Invalid UVD decoding target pitch!\n");
		return -EINVAL;
	}

	if (dpb_size < min_dpb_size) {
		DRM_ERROR("Invalid dpb_size in UVD message (%d / %d)!\n",
			  dpb_size, min_dpb_size);
		return -EINVAL;
	}

	buf_sizes[0x1] = dpb_size;
	buf_sizes[0x2] = image_size;
	buf_sizes[0x4] = min_ctx_size;
	/* store image width to adjust nb memory pstate */
	adev->uvd.decode_image_width = width;
	return 0;
}