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
struct radeonfb_info {scalar_t__ mon1_modedb; scalar_t__ mon2_EDID; scalar_t__ mon1_EDID; int /*<<< orphan*/  fb_base; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  wc_cookie; int /*<<< orphan*/  lvds_timer; int /*<<< orphan*/  init_state; TYPE_2__* pdev; } ;
struct pci_dev {int dummy; } ;
struct fb_info {int /*<<< orphan*/  cmap; struct radeonfb_info* par; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edid1_attr ; 
 int /*<<< orphan*/  edid2_attr ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_destroy_modedb (scalar_t__) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 
 int /*<<< orphan*/  radeon_delete_i2c_busses (struct radeonfb_info*) ; 
 int /*<<< orphan*/  radeon_write_mode (struct radeonfb_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeonfb_bl_exit (struct radeonfb_info*) ; 
 int /*<<< orphan*/  radeonfb_pm_exit (struct radeonfb_info*) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void radeonfb_pci_unregister(struct pci_dev *pdev)
{
        struct fb_info *info = pci_get_drvdata(pdev);
        struct radeonfb_info *rinfo = info->par;
 
        if (!rinfo)
                return;

	radeonfb_pm_exit(rinfo);

	if (rinfo->mon1_EDID)
		sysfs_remove_bin_file(&rinfo->pdev->dev.kobj, &edid1_attr);
	if (rinfo->mon2_EDID)
		sysfs_remove_bin_file(&rinfo->pdev->dev.kobj, &edid2_attr);

#if 0
	/* restore original state
	 * 
	 * Doesn't quite work yet, I suspect if we come from a legacy
	 * VGA mode (or worse, text mode), we need to do some VGA black
	 * magic here that I know nothing about. --BenH
	 */
        radeon_write_mode (rinfo, &rinfo->init_state, 1);
 #endif

	del_timer_sync(&rinfo->lvds_timer);
	arch_phys_wc_del(rinfo->wc_cookie);
        unregister_framebuffer(info);

        radeonfb_bl_exit(rinfo);

        iounmap(rinfo->mmio_base);
        iounmap(rinfo->fb_base);
 
	pci_release_region(pdev, 2);
	pci_release_region(pdev, 0);

	kfree(rinfo->mon1_EDID);
	kfree(rinfo->mon2_EDID);
	if (rinfo->mon1_modedb)
		fb_destroy_modedb(rinfo->mon1_modedb);
#ifdef CONFIG_FB_RADEON_I2C
	radeon_delete_i2c_busses(rinfo);
#endif        
	fb_dealloc_cmap(&info->cmap);
        framebuffer_release(info);
}