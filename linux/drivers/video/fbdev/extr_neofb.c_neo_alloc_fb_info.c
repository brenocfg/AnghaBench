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
struct pci_device_id {int driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct neofb_par {int pci_burst; int lcd_stretch; int /*<<< orphan*/  palette; int /*<<< orphan*/  external_display; int /*<<< orphan*/  internal_display; int /*<<< orphan*/  libretto; } ;
struct TYPE_2__ {int accel; int ypanstep; scalar_t__ ywrapstep; scalar_t__ xpanstep; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct fb_info {int flags; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/ * fbops; TYPE_1__ fix; struct neofb_par* par; } ;

/* Variables and functions */
 int FBINFO_DEFAULT ; 
 int FBINFO_HWACCEL_COPYAREA ; 
 int FBINFO_HWACCEL_FILLRECT ; 
 int FBINFO_HWACCEL_IMAGEBLIT ; 
 int FBINFO_HWACCEL_YPAN ; 
#define  FB_ACCEL_NEOMAGIC_NM2070 136 
#define  FB_ACCEL_NEOMAGIC_NM2090 135 
#define  FB_ACCEL_NEOMAGIC_NM2093 134 
#define  FB_ACCEL_NEOMAGIC_NM2097 133 
#define  FB_ACCEL_NEOMAGIC_NM2160 132 
#define  FB_ACCEL_NEOMAGIC_NM2200 131 
#define  FB_ACCEL_NEOMAGIC_NM2230 130 
#define  FB_ACCEL_NEOMAGIC_NM2360 129 
#define  FB_ACCEL_NEOMAGIC_NM2380 128 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  external ; 
 struct fb_info* framebuffer_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  internal ; 
 int /*<<< orphan*/  libretto ; 
 int /*<<< orphan*/  neofb_ops ; 
 int /*<<< orphan*/  nopciburst ; 
 int /*<<< orphan*/  nostretch ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static struct fb_info *neo_alloc_fb_info(struct pci_dev *dev,
					 const struct pci_device_id *id)
{
	struct fb_info *info;
	struct neofb_par *par;

	info = framebuffer_alloc(sizeof(struct neofb_par), &dev->dev);

	if (!info)
		return NULL;

	par = info->par;

	info->fix.accel = id->driver_data;

	par->pci_burst = !nopciburst;
	par->lcd_stretch = !nostretch;
	par->libretto = libretto;

	par->internal_display = internal;
	par->external_display = external;
	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;

	switch (info->fix.accel) {
	case FB_ACCEL_NEOMAGIC_NM2070:
		snprintf(info->fix.id, sizeof(info->fix.id),
				"MagicGraph 128");
		break;
	case FB_ACCEL_NEOMAGIC_NM2090:
		snprintf(info->fix.id, sizeof(info->fix.id),
				"MagicGraph 128V");
		break;
	case FB_ACCEL_NEOMAGIC_NM2093:
		snprintf(info->fix.id, sizeof(info->fix.id),
				"MagicGraph 128ZV");
		break;
	case FB_ACCEL_NEOMAGIC_NM2097:
		snprintf(info->fix.id, sizeof(info->fix.id),
				"MagicGraph 128ZV+");
		break;
	case FB_ACCEL_NEOMAGIC_NM2160:
		snprintf(info->fix.id, sizeof(info->fix.id),
				"MagicGraph 128XD");
		break;
	case FB_ACCEL_NEOMAGIC_NM2200:
		snprintf(info->fix.id, sizeof(info->fix.id),
				"MagicGraph 256AV");
		info->flags |= FBINFO_HWACCEL_IMAGEBLIT |
		               FBINFO_HWACCEL_COPYAREA |
                	       FBINFO_HWACCEL_FILLRECT;
		break;
	case FB_ACCEL_NEOMAGIC_NM2230:
		snprintf(info->fix.id, sizeof(info->fix.id),
				"MagicGraph 256AV+");
		info->flags |= FBINFO_HWACCEL_IMAGEBLIT |
		               FBINFO_HWACCEL_COPYAREA |
                	       FBINFO_HWACCEL_FILLRECT;
		break;
	case FB_ACCEL_NEOMAGIC_NM2360:
		snprintf(info->fix.id, sizeof(info->fix.id),
				"MagicGraph 256ZX");
		info->flags |= FBINFO_HWACCEL_IMAGEBLIT |
		               FBINFO_HWACCEL_COPYAREA |
                	       FBINFO_HWACCEL_FILLRECT;
		break;
	case FB_ACCEL_NEOMAGIC_NM2380:
		snprintf(info->fix.id, sizeof(info->fix.id),
				"MagicGraph 256XL+");
		info->flags |= FBINFO_HWACCEL_IMAGEBLIT |
		               FBINFO_HWACCEL_COPYAREA |
                	       FBINFO_HWACCEL_FILLRECT;
		break;
	}

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux = 0;
	info->fix.xpanstep = 0;
	info->fix.ypanstep = 4;
	info->fix.ywrapstep = 0;
	info->fix.accel = id->driver_data;

	info->fbops = &neofb_ops;
	info->pseudo_palette = par->palette;
	return info;
}