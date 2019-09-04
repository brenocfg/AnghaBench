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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_pix_format {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;
struct rmi_driver_data {scalar_t__ num_tx_electrodes; scalar_t__ num_rx_electrodes; } ;
struct rmi_device {int /*<<< orphan*/  dev; } ;
struct f54_data {unsigned int input; struct v4l2_pix_format format; void* num_tx_electrodes; void* num_rx_electrodes; TYPE_1__* fn; } ;
typedef  enum rmi_f54_report_type { ____Placeholder_rmi_f54_report_type } rmi_f54_report_type ;
struct TYPE_2__ {struct rmi_device* rmi_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int F54_REPORT_NONE ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_RAW ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct rmi_driver_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int rmi_f54_get_pixel_fmt (int,int /*<<< orphan*/ *) ; 
 int rmi_f54_get_reptype (struct f54_data*,unsigned int) ; 

__attribute__((used)) static int rmi_f54_set_input(struct f54_data *f54, unsigned int i)
{
	struct rmi_device *rmi_dev = f54->fn->rmi_dev;
	struct rmi_driver_data *drv_data = dev_get_drvdata(&rmi_dev->dev);
	u8 rx = drv_data->num_rx_electrodes ? : f54->num_rx_electrodes;
	u8 tx = drv_data->num_tx_electrodes ? : f54->num_tx_electrodes;
	struct v4l2_pix_format *f = &f54->format;
	enum rmi_f54_report_type reptype;
	int ret;

	reptype = rmi_f54_get_reptype(f54, i);
	if (reptype == F54_REPORT_NONE)
		return -EINVAL;

	ret = rmi_f54_get_pixel_fmt(reptype, &f->pixelformat);
	if (ret)
		return ret;

	f54->input = i;

	f->width = rx;
	f->height = tx;
	f->field = V4L2_FIELD_NONE;
	f->colorspace = V4L2_COLORSPACE_RAW;
	f->bytesperline = f->width * sizeof(u16);
	f->sizeimage = f->width * f->height * sizeof(u16);

	return 0;
}