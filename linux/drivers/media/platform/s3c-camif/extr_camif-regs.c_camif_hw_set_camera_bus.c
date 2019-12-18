#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {unsigned int flags; } ;
struct TYPE_6__ {TYPE_2__ sensor; } ;
struct camif_dev {TYPE_1__* variant; TYPE_3__ pdata; } ;
struct TYPE_4__ {scalar_t__ ip_revision; } ;

/* Variables and functions */
 int CIGCTRL_FIELDMODE ; 
 int CIGCTRL_INVPOLFIELD ; 
 int CIGCTRL_INVPOLHREF ; 
 int CIGCTRL_INVPOLPCLK ; 
 int CIGCTRL_INVPOLVSYNC ; 
 scalar_t__ S3C6410_CAMIF_IP_REV ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CIGCTRL ; 
 unsigned int V4L2_MBUS_FIELD_EVEN_LOW ; 
 unsigned int V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 unsigned int V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 unsigned int V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
 int camif_read (struct camif_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_write (struct camif_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

void camif_hw_set_camera_bus(struct camif_dev *camif)
{
	unsigned int flags = camif->pdata.sensor.flags;

	u32 cfg = camif_read(camif, S3C_CAMIF_REG_CIGCTRL);

	cfg &= ~(CIGCTRL_INVPOLPCLK | CIGCTRL_INVPOLVSYNC |
		 CIGCTRL_INVPOLHREF | CIGCTRL_INVPOLFIELD);

	if (flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
		cfg |= CIGCTRL_INVPOLPCLK;

	if (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		cfg |= CIGCTRL_INVPOLVSYNC;
	/*
	 * HREF is normally high during frame active data
	 * transmission and low during horizontal synchronization
	 * period. Thus HREF active high means HSYNC active low.
	 */
	if (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		cfg |= CIGCTRL_INVPOLHREF; /* HREF active low */

	if (camif->variant->ip_revision == S3C6410_CAMIF_IP_REV) {
		if (flags & V4L2_MBUS_FIELD_EVEN_LOW)
			cfg |= CIGCTRL_INVPOLFIELD;
		cfg |= CIGCTRL_FIELDMODE;
	}

	pr_debug("Setting CIGCTRL to: %#x\n", cfg);

	camif_write(camif, S3C_CAMIF_REG_CIGCTRL, cfg);
}