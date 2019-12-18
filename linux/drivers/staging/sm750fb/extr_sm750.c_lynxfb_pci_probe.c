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
struct TYPE_4__ {scalar_t__ vram; } ;
struct TYPE_3__ {int /*<<< orphan*/  de_imageblit; int /*<<< orphan*/  de_copyarea; int /*<<< orphan*/  de_fillrect; int /*<<< orphan*/  de_init; } ;
struct sm750_dev {int /*<<< orphan*/  vidmem_size; int /*<<< orphan*/  pvMem; int /*<<< orphan*/  vidmem_start; TYPE_2__ mtrr; int /*<<< orphan*/  mtrr_off; TYPE_1__ accel; int /*<<< orphan*/  accel_off; int /*<<< orphan*/  slock; struct pci_dev* pdev; int /*<<< orphan*/  revid; int /*<<< orphan*/  devid; int /*<<< orphan*/ ** fbinfo; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  revision; int /*<<< orphan*/  device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ arch_phys_wc_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sm750_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ g_dualview ; 
 int /*<<< orphan*/  g_noaccel ; 
 int /*<<< orphan*/  g_nomtrr ; 
 int /*<<< orphan*/  g_settings ; 
 int /*<<< orphan*/  hw_sm750_inithw (struct sm750_dev*,struct pci_dev*) ; 
 int hw_sm750_map (struct sm750_dev*,struct pci_dev*) ; 
 int lynxfb_kick_out_firmware_fb (struct pci_dev*) ; 
 int /*<<< orphan*/  memset_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct sm750_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  sm750_hw_copyarea ; 
 int /*<<< orphan*/  sm750_hw_de_init ; 
 int /*<<< orphan*/  sm750_hw_fillrect ; 
 int /*<<< orphan*/  sm750_hw_imageblit ; 
 int sm750fb_framebuffer_alloc (struct sm750_dev*,int) ; 
 int /*<<< orphan*/  sm750fb_framebuffer_release (struct sm750_dev*) ; 
 int /*<<< orphan*/  sm750fb_setup (struct sm750_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lynxfb_pci_probe(struct pci_dev *pdev,
			    const struct pci_device_id *ent)
{
	struct sm750_dev *sm750_dev = NULL;
	int max_fb;
	int fbidx;
	int err;

	err = lynxfb_kick_out_firmware_fb(pdev);
	if (err)
		return err;

	/* enable device */
	err = pcim_enable_device(pdev);
	if (err)
		return err;

	err = -ENOMEM;
	sm750_dev = devm_kzalloc(&pdev->dev, sizeof(*sm750_dev), GFP_KERNEL);
	if (!sm750_dev)
		return err;

	sm750_dev->fbinfo[0] = sm750_dev->fbinfo[1] = NULL;
	sm750_dev->devid = pdev->device;
	sm750_dev->revid = pdev->revision;
	sm750_dev->pdev = pdev;
	sm750_dev->mtrr_off = g_nomtrr;
	sm750_dev->mtrr.vram = 0;
	sm750_dev->accel_off = g_noaccel;
	spin_lock_init(&sm750_dev->slock);

	if (!sm750_dev->accel_off) {
		/*
		 * hook deInit and 2d routines, notes that below hw_xxx
		 * routine can work on most of lynx chips
		 * if some chip need specific function,
		 * please hook it in smXXX_set_drv routine
		 */
		sm750_dev->accel.de_init = sm750_hw_de_init;
		sm750_dev->accel.de_fillrect = sm750_hw_fillrect;
		sm750_dev->accel.de_copyarea = sm750_hw_copyarea;
		sm750_dev->accel.de_imageblit = sm750_hw_imageblit;
	}

	/* call chip specific setup routine  */
	sm750fb_setup(sm750_dev, g_settings);

	/* call chip specific mmap routine */
	err = hw_sm750_map(sm750_dev, pdev);
	if (err)
		return err;

	if (!sm750_dev->mtrr_off)
		sm750_dev->mtrr.vram = arch_phys_wc_add(sm750_dev->vidmem_start,
							sm750_dev->vidmem_size);

	memset_io(sm750_dev->pvMem, 0, sm750_dev->vidmem_size);

	pci_set_drvdata(pdev, sm750_dev);

	/* call chipInit routine */
	hw_sm750_inithw(sm750_dev, pdev);

	/* allocate frame buffer info structures according to g_dualview */
	max_fb = g_dualview ? 2 : 1;
	for (fbidx = 0; fbidx < max_fb; fbidx++) {
		err = sm750fb_framebuffer_alloc(sm750_dev, fbidx);
		if (err)
			goto release_fb;
	}

	return 0;

release_fb:
	sm750fb_framebuffer_release(sm750_dev);
	return err;
}