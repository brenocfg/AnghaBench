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
struct gspca_dev {scalar_t__ usb_err; int /*<<< orphan*/  usb_buf; } ;
struct dtcs033_usb_requests {int bRequestType; int wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*,int,int) ; 
 int /*<<< orphan*/  reg_rw (struct gspca_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int reg_reqs(struct gspca_dev *gspca_dev,
		    const struct dtcs033_usb_requests *preqs, int n_reqs)
{
	int i = 0;
	const struct dtcs033_usb_requests *preq;

	while ((i < n_reqs) && (gspca_dev->usb_err >= 0)) {

		preq = &preqs[i];

		reg_rw(gspca_dev, preq->bRequestType, preq->bRequest,
			preq->wValue, preq->wIndex, preq->wLength);

		if (gspca_dev->usb_err < 0) {

			gspca_err(gspca_dev, "usb error request no: %d / %d\n",
				  i, n_reqs);
		} else if (preq->bRequestType & USB_DIR_IN) {

			gspca_dbg(gspca_dev, D_STREAM,
				  "USB IN (%d) returned[%d] %3ph %s",
				  i,
				  preq->wLength,
				  gspca_dev->usb_buf,
				  preq->wLength > 3 ? "...\n" : "\n");
		}

		i++;
	}
	return gspca_dev->usb_err;
}