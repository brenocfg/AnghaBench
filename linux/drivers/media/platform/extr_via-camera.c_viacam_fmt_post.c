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
struct via_format {int bpp; } ;
struct v4l2_pix_format {int bytesperline; int width; int sizeimage; int height; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 struct via_format* via_find_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void viacam_fmt_post(struct v4l2_pix_format *userfmt,
		struct v4l2_pix_format *sensorfmt)
{
	struct via_format *f = via_find_format(userfmt->pixelformat);

	sensorfmt->bytesperline = sensorfmt->width * f->bpp;
	sensorfmt->sizeimage = sensorfmt->height * sensorfmt->bytesperline;
	userfmt->pixelformat = sensorfmt->pixelformat;
	userfmt->field = sensorfmt->field;
	userfmt->bytesperline = 2 * userfmt->width;
	userfmt->sizeimage = userfmt->bytesperline * userfmt->height;
	userfmt->colorspace = sensorfmt->colorspace;
	userfmt->ycbcr_enc = sensorfmt->ycbcr_enc;
	userfmt->quantization = sensorfmt->quantization;
	userfmt->xfer_func = sensorfmt->xfer_func;
}