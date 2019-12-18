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
typedef  int u32 ;
struct v4l2_mbus_framefmt {int code; int width; int height; } ;
struct camif_dev {int /*<<< orphan*/  dev; struct v4l2_mbus_framefmt mbus_fmt; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int CISRCFMT_ORDER422_MASK ; 
 int CISRCFMT_SIZE_CAM_MASK ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CISRCFMT ; 
 int camif_read (struct camif_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_write (struct camif_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int** src_pixfmt_map ; 

void camif_hw_set_source_format(struct camif_dev *camif)
{
	struct v4l2_mbus_framefmt *mf = &camif->mbus_fmt;
	int i;
	u32 cfg;

	for (i = ARRAY_SIZE(src_pixfmt_map) - 1; i >= 0; i--) {
		if (src_pixfmt_map[i][0] == mf->code)
			break;
	}
	if (i < 0) {
		i = 0;
		dev_err(camif->dev,
			"Unsupported pixel code, falling back to %#08x\n",
			src_pixfmt_map[i][0]);
	}

	cfg = camif_read(camif, S3C_CAMIF_REG_CISRCFMT);
	cfg &= ~(CISRCFMT_ORDER422_MASK | CISRCFMT_SIZE_CAM_MASK);
	cfg |= (mf->width << 16) | mf->height;
	cfg |= src_pixfmt_map[i][1];
	camif_write(camif, S3C_CAMIF_REG_CISRCFMT, cfg);
}