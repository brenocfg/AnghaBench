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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  poxxxx_gamma ; 
 int /*<<< orphan*/  usb_exchange (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setgamma(struct gspca_dev *gspca_dev)
{
/*fixme:to do */
	usb_exchange(gspca_dev, poxxxx_gamma);
}