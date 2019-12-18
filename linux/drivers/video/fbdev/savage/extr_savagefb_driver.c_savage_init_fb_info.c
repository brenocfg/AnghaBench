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
struct savagefb_par {scalar_t__ chip; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/  SavageWaitFifo; int /*<<< orphan*/  SavageWaitIdle; struct pci_dev* pcidev; } ;
struct pci_device_id {int driver_data; } ;
struct pci_dev {int dummy; } ;
struct TYPE_5__ {int size; int scan_align; int buf_align; int access_align; scalar_t__ addr; } ;
struct TYPE_4__ {int width; int height; scalar_t__ accel_flags; int /*<<< orphan*/  activate; scalar_t__ nonstd; } ;
struct TYPE_6__ {int ypanstep; int accel; int /*<<< orphan*/  id; scalar_t__ ywrapstep; scalar_t__ type_aux; int /*<<< orphan*/  type; } ;
struct fb_info {int flags; int /*<<< orphan*/  cmap; TYPE_2__ pixmap; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/ * fbops; TYPE_1__ var; TYPE_3__ fix; struct savagefb_par* par; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FBINFO_DEFAULT ; 
 int FBINFO_HWACCEL_COPYAREA ; 
 int FBINFO_HWACCEL_FILLRECT ; 
 int FBINFO_HWACCEL_IMAGEBLIT ; 
 int FBINFO_HWACCEL_XPAN ; 
 int FBINFO_HWACCEL_YPAN ; 
#define  FB_ACCEL_PROSAVAGE_DDR 142 
#define  FB_ACCEL_PROSAVAGE_DDRK 141 
#define  FB_ACCEL_PROSAVAGE_KM 140 
#define  FB_ACCEL_PROSAVAGE_PM 139 
#define  FB_ACCEL_S3TWISTER_K 138 
#define  FB_ACCEL_S3TWISTER_P 137 
#define  FB_ACCEL_SAVAGE2000 136 
#define  FB_ACCEL_SAVAGE3D 135 
#define  FB_ACCEL_SAVAGE3D_MV 134 
#define  FB_ACCEL_SAVAGE4 133 
#define  FB_ACCEL_SAVAGE_IX 132 
#define  FB_ACCEL_SAVAGE_IX_MV 131 
#define  FB_ACCEL_SAVAGE_MX 130 
#define  FB_ACCEL_SAVAGE_MX_MV 129 
#define  FB_ACCEL_SUPERSAVAGE 128 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NR_PALETTE ; 
 void* S3_PROSAVAGE ; 
 void* S3_PROSAVAGEDDR ; 
 scalar_t__ S3_SAVAGE2000 ; 
 void* S3_SAVAGE3D ; 
 scalar_t__ S3_SAVAGE3D_SERIES (scalar_t__) ; 
 scalar_t__ S3_SAVAGE4 ; 
 scalar_t__ S3_SAVAGE4_SERIES (scalar_t__) ; 
 void* S3_SAVAGE_MX ; 
 scalar_t__ S3_SUPERSAVAGE ; 
 void* S3_TWISTER ; 
 int fb_alloc_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savage2000_waitfifo ; 
 int /*<<< orphan*/  savage2000_waitidle ; 
 int /*<<< orphan*/  savage3D_waitfifo ; 
 int /*<<< orphan*/  savage3D_waitidle ; 
 int /*<<< orphan*/  savage4_waitfifo ; 
 int /*<<< orphan*/  savage4_waitidle ; 
 int /*<<< orphan*/  savagefb_ops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int savage_init_fb_info(struct fb_info *info, struct pci_dev *dev,
			       const struct pci_device_id *id)
{
	struct savagefb_par *par = info->par;
	int err = 0;

	par->pcidev  = dev;

	info->fix.type	   = FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux	   = 0;
	info->fix.ypanstep	   = 1;
	info->fix.ywrapstep   = 0;
	info->fix.accel       = id->driver_data;

	switch (info->fix.accel) {
	case FB_ACCEL_SUPERSAVAGE:
		par->chip = S3_SUPERSAVAGE;
		snprintf(info->fix.id, 16, "SuperSavage");
		break;
	case FB_ACCEL_SAVAGE4:
		par->chip = S3_SAVAGE4;
		snprintf(info->fix.id, 16, "Savage4");
		break;
	case FB_ACCEL_SAVAGE3D:
		par->chip = S3_SAVAGE3D;
		snprintf(info->fix.id, 16, "Savage3D");
		break;
	case FB_ACCEL_SAVAGE3D_MV:
		par->chip = S3_SAVAGE3D;
		snprintf(info->fix.id, 16, "Savage3D-MV");
		break;
	case FB_ACCEL_SAVAGE2000:
		par->chip = S3_SAVAGE2000;
		snprintf(info->fix.id, 16, "Savage2000");
		break;
	case FB_ACCEL_SAVAGE_MX_MV:
		par->chip = S3_SAVAGE_MX;
		snprintf(info->fix.id, 16, "Savage/MX-MV");
		break;
	case FB_ACCEL_SAVAGE_MX:
		par->chip = S3_SAVAGE_MX;
		snprintf(info->fix.id, 16, "Savage/MX");
		break;
	case FB_ACCEL_SAVAGE_IX_MV:
		par->chip = S3_SAVAGE_MX;
		snprintf(info->fix.id, 16, "Savage/IX-MV");
		break;
	case FB_ACCEL_SAVAGE_IX:
		par->chip = S3_SAVAGE_MX;
		snprintf(info->fix.id, 16, "Savage/IX");
		break;
	case FB_ACCEL_PROSAVAGE_PM:
		par->chip = S3_PROSAVAGE;
		snprintf(info->fix.id, 16, "ProSavagePM");
		break;
	case FB_ACCEL_PROSAVAGE_KM:
		par->chip = S3_PROSAVAGE;
		snprintf(info->fix.id, 16, "ProSavageKM");
		break;
	case FB_ACCEL_S3TWISTER_P:
		par->chip = S3_TWISTER;
		snprintf(info->fix.id, 16, "TwisterP");
		break;
	case FB_ACCEL_S3TWISTER_K:
		par->chip = S3_TWISTER;
		snprintf(info->fix.id, 16, "TwisterK");
		break;
	case FB_ACCEL_PROSAVAGE_DDR:
		par->chip = S3_PROSAVAGEDDR;
		snprintf(info->fix.id, 16, "ProSavageDDR");
		break;
	case FB_ACCEL_PROSAVAGE_DDRK:
		par->chip = S3_PROSAVAGEDDR;
		snprintf(info->fix.id, 16, "ProSavage8");
		break;
	}

	if (S3_SAVAGE3D_SERIES(par->chip)) {
		par->SavageWaitIdle = savage3D_waitidle;
		par->SavageWaitFifo = savage3D_waitfifo;
	} else if (S3_SAVAGE4_SERIES(par->chip) ||
		   S3_SUPERSAVAGE == par->chip) {
		par->SavageWaitIdle = savage4_waitidle;
		par->SavageWaitFifo = savage4_waitfifo;
	} else {
		par->SavageWaitIdle = savage2000_waitidle;
		par->SavageWaitFifo = savage2000_waitfifo;
	}

	info->var.nonstd      = 0;
	info->var.activate    = FB_ACTIVATE_NOW;
	info->var.width       = -1;
	info->var.height      = -1;
	info->var.accel_flags = 0;

	info->fbops          = &savagefb_ops;
	info->flags          = FBINFO_DEFAULT |
		               FBINFO_HWACCEL_YPAN |
		               FBINFO_HWACCEL_XPAN;

	info->pseudo_palette = par->pseudo_palette;

#if defined(CONFIG_FB_SAVAGE_ACCEL)
	/* FIFO size + padding for commands */
	info->pixmap.addr = kcalloc(8, 1024, GFP_KERNEL);

	err = -ENOMEM;
	if (info->pixmap.addr) {
		info->pixmap.size = 8*1024;
		info->pixmap.scan_align = 4;
		info->pixmap.buf_align = 4;
		info->pixmap.access_align = 32;

		err = fb_alloc_cmap(&info->cmap, NR_PALETTE, 0);
		if (!err)
			info->flags |= FBINFO_HWACCEL_COPYAREA |
				       FBINFO_HWACCEL_FILLRECT |
				       FBINFO_HWACCEL_IMAGEBLIT;
	}
#endif
	return err;
}