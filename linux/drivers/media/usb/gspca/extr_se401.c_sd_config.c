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
typedef  int u8 ;
struct usb_device_id {int dummy; } ;
struct sd {int resetlevel; int has_brightness; TYPE_1__* fmts; } ;
struct cam {int nmodes; int bulk; int bulk_nurbs; int /*<<< orphan*/  bulk_size; TYPE_1__* cam_mode; } ;
struct gspca_dev {int* usb_buf; int usb_err; int /*<<< orphan*/  dev; struct cam cam; } ;
struct TYPE_2__ {int width; int height; int priv; int bytesperline; int sizeimage; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_SIZE ; 
 int ENODEV ; 
 int MAX_MODES ; 
 int SE401_FORMAT_BAYER ; 
 int /*<<< orphan*/  SE401_REQ_GET_BRT ; 
 int /*<<< orphan*/  SE401_REQ_GET_CAMERA_DESCRIPTOR ; 
 int /*<<< orphan*/  SE401_REQ_LED_CONTROL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_SBGGR8 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_SE401 ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int,...) ; 
 int /*<<< orphan*/  se401_read_req (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  se401_write_req (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_reset_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *)gspca_dev;
	struct cam *cam = &gspca_dev->cam;
	u8 *cd = gspca_dev->usb_buf;
	int i, j, n;
	int widths[MAX_MODES], heights[MAX_MODES];

	/* Read the camera descriptor */
	se401_read_req(gspca_dev, SE401_REQ_GET_CAMERA_DESCRIPTOR, 1);
	if (gspca_dev->usb_err) {
		/* Sometimes after being idle for a while the se401 won't
		   respond and needs a good kicking  */
		usb_reset_device(gspca_dev->dev);
		gspca_dev->usb_err = 0;
		se401_read_req(gspca_dev, SE401_REQ_GET_CAMERA_DESCRIPTOR, 0);
	}

	/* Some cameras start with their LED on */
	se401_write_req(gspca_dev, SE401_REQ_LED_CONTROL, 0, 0);
	if (gspca_dev->usb_err)
		return gspca_dev->usb_err;

	if (cd[1] != 0x41) {
		pr_err("Wrong descriptor type\n");
		return -ENODEV;
	}

	if (!(cd[2] & SE401_FORMAT_BAYER)) {
		pr_err("Bayer format not supported!\n");
		return -ENODEV;
	}

	if (cd[3])
		pr_info("ExtraFeatures: %d\n", cd[3]);

	n = cd[4] | (cd[5] << 8);
	if (n > MAX_MODES) {
		pr_err("Too many frame sizes\n");
		return -ENODEV;
	}

	for (i = 0; i < n ; i++) {
		widths[i] = cd[6 + i * 4 + 0] | (cd[6 + i * 4 + 1] << 8);
		heights[i] = cd[6 + i * 4 + 2] | (cd[6 + i * 4 + 3] << 8);
	}

	for (i = 0; i < n ; i++) {
		sd->fmts[i].width = widths[i];
		sd->fmts[i].height = heights[i];
		sd->fmts[i].field = V4L2_FIELD_NONE;
		sd->fmts[i].colorspace = V4L2_COLORSPACE_SRGB;
		sd->fmts[i].priv = 1;

		/* janggu compression only works for 1/4th or 1/16th res */
		for (j = 0; j < n; j++) {
			if (widths[j] / 2 == widths[i] &&
			    heights[j] / 2 == heights[i]) {
				sd->fmts[i].priv = 2;
				break;
			}
		}
		/* 1/16th if available too is better then 1/4th, because
		   we then use a larger area of the sensor */
		for (j = 0; j < n; j++) {
			if (widths[j] / 4 == widths[i] &&
			    heights[j] / 4 == heights[i]) {
				sd->fmts[i].priv = 4;
				break;
			}
		}

		if (sd->fmts[i].priv == 1) {
			/* Not a 1/4th or 1/16th res, use bayer */
			sd->fmts[i].pixelformat = V4L2_PIX_FMT_SBGGR8;
			sd->fmts[i].bytesperline = widths[i];
			sd->fmts[i].sizeimage = widths[i] * heights[i];
			pr_info("Frame size: %dx%d bayer\n",
				widths[i], heights[i]);
		} else {
			/* Found a match use janggu compression */
			sd->fmts[i].pixelformat = V4L2_PIX_FMT_SE401;
			sd->fmts[i].bytesperline = 0;
			sd->fmts[i].sizeimage = widths[i] * heights[i] * 3;
			pr_info("Frame size: %dx%d 1/%dth janggu\n",
				widths[i], heights[i],
				sd->fmts[i].priv * sd->fmts[i].priv);
		}
	}

	cam->cam_mode = sd->fmts;
	cam->nmodes = n;
	cam->bulk = 1;
	cam->bulk_size = BULK_SIZE;
	cam->bulk_nurbs = 4;
	sd->resetlevel = 0x2d; /* Set initial resetlevel */

	/* See if the camera supports brightness */
	se401_read_req(gspca_dev, SE401_REQ_GET_BRT, 1);
	sd->has_brightness = !!gspca_dev->usb_err;
	gspca_dev->usb_err = 0;

	return 0;
}