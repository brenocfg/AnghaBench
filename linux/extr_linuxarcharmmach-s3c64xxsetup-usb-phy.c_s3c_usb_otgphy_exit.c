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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C64XX_OTHERS ; 
 int S3C64XX_OTHERS_USBMASK ; 
 int /*<<< orphan*/  S3C_PHYPWR ; 
 int S3C_PHYPWR_ANALOG_POWERDOWN ; 
 int S3C_PHYPWR_OTG_DISABLE ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c_usb_otgphy_exit(struct platform_device *pdev)
{
	writel((readl(S3C_PHYPWR) | S3C_PHYPWR_ANALOG_POWERDOWN |
				S3C_PHYPWR_OTG_DISABLE), S3C_PHYPWR);

	writel(readl(S3C64XX_OTHERS) & ~S3C64XX_OTHERS_USBMASK, S3C64XX_OTHERS);

	return 0;
}