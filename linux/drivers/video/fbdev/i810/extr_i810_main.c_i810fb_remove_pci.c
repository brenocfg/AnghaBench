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
struct pci_dev {int dummy; } ;
struct i810fb_par {int dummy; } ;
struct fb_info {struct i810fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  i810fb_release_resource (struct fb_info*,struct i810fb_par*) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void i810fb_remove_pci(struct pci_dev *dev)
{
	struct fb_info *info = pci_get_drvdata(dev);
	struct i810fb_par *par = info->par;

	unregister_framebuffer(info);  
	i810fb_release_resource(info, par);
	printk("cleanup_module:  unloaded i810 framebuffer device\n");
}