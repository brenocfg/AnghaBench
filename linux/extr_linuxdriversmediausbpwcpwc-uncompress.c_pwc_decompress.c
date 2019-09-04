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
typedef  int /*<<< orphan*/  u16 ;
struct pwc_raw_frame {struct pwc_raw_frame* cmd; void* vbandlength; void* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  vb2_buf; } ;
struct pwc_frame_buf {TYPE_1__ vb; void* data; } ;
struct pwc_device {int frame_header_size; scalar_t__ pixfmt; scalar_t__ type; scalar_t__ vbandlength; void* cmd_buf; int frame_size; int width; int height; } ;

/* Variables and functions */
 scalar_t__ DEVICE_USE_CODEC1 (scalar_t__) ; 
 int ENXIO ; 
 int /*<<< orphan*/  PWC_ERROR (char*) ; 
 scalar_t__ V4L2_PIX_FMT_YUV420 ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct pwc_raw_frame*,void*,int) ; 
 int /*<<< orphan*/  pwc_dec23_decompress (struct pwc_device*,void*,void*) ; 
 void* vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int pwc_decompress(struct pwc_device *pdev, struct pwc_frame_buf *fbuf)
{
	int n, line, col;
	void *yuv, *image;
	u16 *src;
	u16 *dsty, *dstu, *dstv;

	image = vb2_plane_vaddr(&fbuf->vb.vb2_buf, 0);

	yuv = fbuf->data + pdev->frame_header_size;  /* Skip header */

	/* Raw format; that's easy... */
	if (pdev->pixfmt != V4L2_PIX_FMT_YUV420)
	{
		struct pwc_raw_frame *raw_frame = image;
		raw_frame->type = cpu_to_le16(pdev->type);
		raw_frame->vbandlength = cpu_to_le16(pdev->vbandlength);
			/* cmd_buf is always 4 bytes, but sometimes, only the
			 * first 3 bytes is filled (Nala case). We can
			 * determine this using the type of the webcam */
		memcpy(raw_frame->cmd, pdev->cmd_buf, 4);
		memcpy(raw_frame+1, yuv, pdev->frame_size);
		vb2_set_plane_payload(&fbuf->vb.vb2_buf, 0,
			pdev->frame_size + sizeof(struct pwc_raw_frame));
		return 0;
	}

	vb2_set_plane_payload(&fbuf->vb.vb2_buf, 0,
			      pdev->width * pdev->height * 3 / 2);

	if (pdev->vbandlength == 0) {
		/* Uncompressed mode.
		 *
		 * We do some byte shuffling here to go from the
		 * native format to YUV420P.
		 */
		src = (u16 *)yuv;
		n = pdev->width * pdev->height;
		dsty = (u16 *)(image);
		dstu = (u16 *)(image + n);
		dstv = (u16 *)(image + n + n / 4);

		for (line = 0; line < pdev->height; line++) {
			for (col = 0; col < pdev->width; col += 4) {
				*dsty++ = *src++;
				*dsty++ = *src++;
				if (line & 1)
					*dstv++ = *src++;
				else
					*dstu++ = *src++;
			}
		}

		return 0;
	}

	/*
	 * Compressed;
	 * the decompressor routines will write the data in planar format
	 * immediately.
	 */
	if (DEVICE_USE_CODEC1(pdev->type)) {

		/* TODO & FIXME */
		PWC_ERROR("This chipset is not supported for now\n");
		return -ENXIO; /* No such device or address: missing decompressor */

	} else {
		pwc_dec23_decompress(pdev, yuv, image);
	}
	return 0;
}