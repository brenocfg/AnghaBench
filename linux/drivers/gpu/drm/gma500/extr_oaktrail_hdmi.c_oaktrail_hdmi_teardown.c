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
struct oaktrail_hdmi_dev {int /*<<< orphan*/  regs; struct pci_dev* dev; } ;
struct drm_psb_private {struct oaktrail_hdmi_dev* hdmi_priv; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct oaktrail_hdmi_dev*) ; 
 int /*<<< orphan*/  oaktrail_hdmi_i2c_exit (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

void oaktrail_hdmi_teardown(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	struct pci_dev *pdev;

	if (hdmi_dev) {
		pdev = hdmi_dev->dev;
		pci_set_drvdata(pdev, NULL);
		oaktrail_hdmi_i2c_exit(pdev);
		iounmap(hdmi_dev->regs);
		kfree(hdmi_dev);
		pci_dev_put(pdev);
	}
}