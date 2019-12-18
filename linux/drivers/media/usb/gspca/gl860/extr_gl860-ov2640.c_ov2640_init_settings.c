#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int backlight; int brightness; int sharpness; int contrast; int gamma; int hue; int saturation; int whitebal; int mirror; int flip; scalar_t__ AC50Hz; } ;
struct TYPE_3__ {int backlight; int sharpness; int gamma; int saturation; int whitebal; scalar_t__ flip; scalar_t__ mirror; scalar_t__ hue; scalar_t__ contrast; scalar_t__ brightness; } ;
struct sd {int /*<<< orphan*/  dev_post_unset_alt; int /*<<< orphan*/  dev_init_pre_alt; int /*<<< orphan*/  dev_configure_alt; int /*<<< orphan*/  dev_init_at_startup; int /*<<< orphan*/  dev_camera_settings; TYPE_2__ vmax; TYPE_1__ vcur; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ov2640_camera_settings ; 
 int /*<<< orphan*/  ov2640_configure_alt ; 
 int /*<<< orphan*/  ov2640_init_at_startup ; 
 int /*<<< orphan*/  ov2640_init_pre_alt ; 
 int /*<<< orphan*/  ov2640_post_unset_alt ; 

void ov2640_init_settings(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->vcur.backlight  =  32;
	sd->vcur.brightness =   0;
	sd->vcur.sharpness  =   6;
	sd->vcur.contrast   =   0;
	sd->vcur.gamma      =  32;
	sd->vcur.hue        =   0;
	sd->vcur.saturation = 128;
	sd->vcur.whitebal   =  64;
	sd->vcur.mirror     =   0;
	sd->vcur.flip       =   0;

	sd->vmax.backlight  =  64;
	sd->vmax.brightness = 255;
	sd->vmax.sharpness  =  31;
	sd->vmax.contrast   = 255;
	sd->vmax.gamma      =  64;
	sd->vmax.hue        = 254 + 2;
	sd->vmax.saturation = 255;
	sd->vmax.whitebal   = 128;
	sd->vmax.mirror     = 1;
	sd->vmax.flip       = 1;
	sd->vmax.AC50Hz     = 0;

	sd->dev_camera_settings = ov2640_camera_settings;
	sd->dev_init_at_startup = ov2640_init_at_startup;
	sd->dev_configure_alt   = ov2640_configure_alt;
	sd->dev_init_pre_alt    = ov2640_init_pre_alt;
	sd->dev_post_unset_alt  = ov2640_post_unset_alt;
}