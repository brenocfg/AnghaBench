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
typedef  int u32 ;
struct v4l2_rect {int left; int top; int width; int height; } ;
struct v4l2_mbus_framefmt {int width; int height; } ;
struct camif_dev {TYPE_1__* variant; struct v4l2_rect camif_crop; struct v4l2_mbus_framefmt mbus_fmt; } ;
struct TYPE_2__ {scalar_t__ ip_revision; } ;

/* Variables and functions */
 int CIWDOFST_OFST_MASK ; 
 int CIWDOFST_WINOFSEN ; 
 scalar_t__ S3C6410_CAMIF_IP_REV ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CIWDOFST ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CIWDOFST2 ; 
 int camif_read (struct camif_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_write (struct camif_dev*,int /*<<< orphan*/ ,int) ; 

void camif_hw_set_camera_crop(struct camif_dev *camif)
{
	struct v4l2_mbus_framefmt *mf = &camif->mbus_fmt;
	struct v4l2_rect *crop = &camif->camif_crop;
	u32 hoff2, voff2;
	u32 cfg;

	/* Note: s3c244x requirement: left = f_width - rect.width / 2 */
	cfg = camif_read(camif, S3C_CAMIF_REG_CIWDOFST);
	cfg &= ~(CIWDOFST_OFST_MASK | CIWDOFST_WINOFSEN);
	cfg |= (crop->left << 16) | crop->top;
	if (crop->left != 0 || crop->top != 0)
		cfg |= CIWDOFST_WINOFSEN;
	camif_write(camif, S3C_CAMIF_REG_CIWDOFST, cfg);

	if (camif->variant->ip_revision == S3C6410_CAMIF_IP_REV) {
		hoff2 = mf->width - crop->width - crop->left;
		voff2 = mf->height - crop->height - crop->top;
		cfg = (hoff2 << 16) | voff2;
		camif_write(camif, S3C_CAMIF_REG_CIWDOFST2, cfg);
	}
}