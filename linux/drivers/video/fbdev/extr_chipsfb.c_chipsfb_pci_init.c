#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; TYPE_1__* resource; } ;
struct TYPE_8__ {int smem_len; } ;
struct fb_info {int /*<<< orphan*/ * screen_base; TYPE_3__ fix; int /*<<< orphan*/  node; } ;
struct TYPE_7__ {int /*<<< orphan*/  power; } ;
struct TYPE_9__ {TYPE_2__ props; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  backlight_update_status (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 struct fb_info* framebuffer_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  init_chips (struct fb_info*,unsigned long) ; 
 int /*<<< orphan*/ * ioremap (unsigned long,int) ; 
 int /*<<< orphan*/ * ioremap_wc (unsigned long,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,unsigned short*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_request_region (struct pci_dev*,int /*<<< orphan*/ ,char*) ; 
 unsigned long pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct fb_info*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,unsigned short) ; 
 TYPE_4__* pmac_backlight ; 
 int /*<<< orphan*/  pmac_backlight_mutex ; 
 scalar_t__ register_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int chipsfb_pci_init(struct pci_dev *dp, const struct pci_device_id *ent)
{
	struct fb_info *p;
	unsigned long addr;
	unsigned short cmd;
	int rc = -ENODEV;

	if (pci_enable_device(dp) < 0) {
		dev_err(&dp->dev, "Cannot enable PCI device\n");
		goto err_out;
	}

	if ((dp->resource[0].flags & IORESOURCE_MEM) == 0)
		goto err_disable;
	addr = pci_resource_start(dp, 0);
	if (addr == 0)
		goto err_disable;

	p = framebuffer_alloc(0, &dp->dev);
	if (p == NULL) {
		rc = -ENOMEM;
		goto err_disable;
	}

	if (pci_request_region(dp, 0, "chipsfb") != 0) {
		dev_err(&dp->dev, "Cannot request framebuffer\n");
		rc = -EBUSY;
		goto err_release_fb;
	}

#ifdef __BIG_ENDIAN
	addr += 0x800000;	// Use big-endian aperture
#endif

	/* we should use pci_enable_device here, but,
	   the device doesn't declare its I/O ports in its BARs
	   so pci_enable_device won't turn on I/O responses */
	pci_read_config_word(dp, PCI_COMMAND, &cmd);
	cmd |= 3;	/* enable memory and IO space */
	pci_write_config_word(dp, PCI_COMMAND, cmd);

#ifdef CONFIG_PMAC_BACKLIGHT
	/* turn on the backlight */
	mutex_lock(&pmac_backlight_mutex);
	if (pmac_backlight) {
		pmac_backlight->props.power = FB_BLANK_UNBLANK;
		backlight_update_status(pmac_backlight);
	}
	mutex_unlock(&pmac_backlight_mutex);
#endif /* CONFIG_PMAC_BACKLIGHT */

#ifdef CONFIG_PPC
	p->screen_base = ioremap_wc(addr, 0x200000);
#else
	p->screen_base = ioremap(addr, 0x200000);
#endif
	if (p->screen_base == NULL) {
		dev_err(&dp->dev, "Cannot map framebuffer\n");
		rc = -ENOMEM;
		goto err_release_pci;
	}

	pci_set_drvdata(dp, p);

	init_chips(p, addr);

	if (register_framebuffer(p) < 0) {
		dev_err(&dp->dev,"C&T 65550 framebuffer failed to register\n");
		goto err_unmap;
	}

	dev_info(&dp->dev,"fb%d: Chips 65550 frame buffer"
		 " (%dK RAM detected)\n",
		 p->node, p->fix.smem_len / 1024);

	return 0;

 err_unmap:
	iounmap(p->screen_base);
 err_release_pci:
	pci_release_region(dp, 0);
 err_release_fb:
	framebuffer_release(p);
 err_disable:
 err_out:
	return rc;
}