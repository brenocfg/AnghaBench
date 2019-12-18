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
struct v4l2_pix_format {scalar_t__ width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct solo_enc_dev {int /*<<< orphan*/  fmt; int /*<<< orphan*/  mode; int /*<<< orphan*/  vidq; struct solo_dev* solo_dev; } ;
struct solo_dev {scalar_t__ video_hsize; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SOLO_ENC_MODE_CIF ; 
 int /*<<< orphan*/  SOLO_ENC_MODE_D1 ; 
 int solo_enc_try_fmt_cap (struct file*,void*,struct v4l2_format*) ; 
 int /*<<< orphan*/  solo_update_mode (struct solo_enc_dev*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct solo_enc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int solo_enc_set_fmt_cap(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct solo_enc_dev *solo_enc = video_drvdata(file);
	struct solo_dev *solo_dev = solo_enc->solo_dev;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	int ret;

	if (vb2_is_busy(&solo_enc->vidq))
		return -EBUSY;

	ret = solo_enc_try_fmt_cap(file, priv, f);
	if (ret)
		return ret;

	if (pix->width == solo_dev->video_hsize)
		solo_enc->mode = SOLO_ENC_MODE_D1;
	else
		solo_enc->mode = SOLO_ENC_MODE_CIF;

	/* This does not change the encoder at all */
	solo_enc->fmt = pix->pixelformat;

	/*
	 * More information is needed about these 'extended' types. As far
	 * as I can tell these are basically additional video streams with
	 * different MPEG encoding attributes that can run in parallel with
	 * the main stream. If so, then this should be implemented as a
	 * second video node. Abusing priv like this is certainly not the
	 * right approach.
	if (pix->priv)
		solo_enc->type = SOLO_ENC_TYPE_EXT;
	 */
	solo_update_mode(solo_enc);
	return 0;
}