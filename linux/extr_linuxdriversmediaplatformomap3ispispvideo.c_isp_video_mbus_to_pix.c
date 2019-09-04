#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format {unsigned int bytesperline; unsigned int width; int height; int sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct v4l2_mbus_framefmt {unsigned int width; int height; scalar_t__ code; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; } ;
struct isp_video {int /*<<< orphan*/  bpl_alignment; int /*<<< orphan*/  bpl_zero_padding; int /*<<< orphan*/  bpl_max; } ;
struct TYPE_3__ {scalar_t__ code; unsigned int bpp; int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int clamp (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* formats ; 
 int /*<<< orphan*/  memset (struct v4l2_pix_format*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int isp_video_mbus_to_pix(const struct isp_video *video,
					  const struct v4l2_mbus_framefmt *mbus,
					  struct v4l2_pix_format *pix)
{
	unsigned int bpl = pix->bytesperline;
	unsigned int min_bpl;
	unsigned int i;

	memset(pix, 0, sizeof(*pix));
	pix->width = mbus->width;
	pix->height = mbus->height;

	for (i = 0; i < ARRAY_SIZE(formats); ++i) {
		if (formats[i].code == mbus->code)
			break;
	}

	if (WARN_ON(i == ARRAY_SIZE(formats)))
		return 0;

	min_bpl = pix->width * formats[i].bpp;

	/* Clamp the requested bytes per line value. If the maximum bytes per
	 * line value is zero, the module doesn't support user configurable line
	 * sizes. Override the requested value with the minimum in that case.
	 */
	if (video->bpl_max)
		bpl = clamp(bpl, min_bpl, video->bpl_max);
	else
		bpl = min_bpl;

	if (!video->bpl_zero_padding || bpl != min_bpl)
		bpl = ALIGN(bpl, video->bpl_alignment);

	pix->pixelformat = formats[i].pixelformat;
	pix->bytesperline = bpl;
	pix->sizeimage = pix->bytesperline * pix->height;
	pix->colorspace = mbus->colorspace;
	pix->field = mbus->field;

	return bpl - min_bpl;
}