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
struct usb_hcd {int dummy; } ;
struct s3c2410_hcd_info {int /*<<< orphan*/  (* enable_oc ) (struct s3c2410_hcd_info*,int) ;int /*<<< orphan*/  report_oc; struct usb_hcd* hcd; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct s3c2410_hcd_info* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  s3c2410_hcd_oc ; 
 int /*<<< orphan*/  stub1 (struct s3c2410_hcd_info*,int) ; 
 int /*<<< orphan*/  usb_clk ; 

__attribute__((used)) static void s3c2410_start_hc(struct platform_device *dev, struct usb_hcd *hcd)
{
	struct s3c2410_hcd_info *info = dev_get_platdata(&dev->dev);

	dev_dbg(&dev->dev, "s3c2410_start_hc:\n");

	clk_prepare_enable(usb_clk);
	mdelay(2);			/* let the bus clock stabilise */

	clk_prepare_enable(clk);

	if (info != NULL) {
		info->hcd	= hcd;
		info->report_oc = s3c2410_hcd_oc;

		if (info->enable_oc != NULL)
			(info->enable_oc)(info, 1);
	}
}