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
struct oaktrail_hdmi_dev {struct pci_dev* dev; int /*<<< orphan*/  regs; int /*<<< orphan*/  mmio_len; int /*<<< orphan*/  mmio; } ;
struct drm_psb_private {struct oaktrail_hdmi_dev* hdmi_priv; } ;
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct oaktrail_hdmi_dev*) ; 
 struct oaktrail_hdmi_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oaktrail_hdmi_audio_disable (struct drm_device*) ; 
 int oaktrail_hdmi_i2c_init (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct oaktrail_hdmi_dev*) ; 

void oaktrail_hdmi_setup(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct pci_dev *pdev;
	struct oaktrail_hdmi_dev *hdmi_dev;
	int ret;

	pdev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x080d, NULL);
	if (!pdev)
		return;

	hdmi_dev = kzalloc(sizeof(struct oaktrail_hdmi_dev), GFP_KERNEL);
	if (!hdmi_dev) {
		dev_err(dev->dev, "failed to allocate memory\n");
		goto out;
	}


	ret = pci_enable_device(pdev);
	if (ret) {
		dev_err(dev->dev, "failed to enable hdmi controller\n");
		goto free;
	}

	hdmi_dev->mmio = pci_resource_start(pdev, 0);
	hdmi_dev->mmio_len = pci_resource_len(pdev, 0);
	hdmi_dev->regs = ioremap(hdmi_dev->mmio, hdmi_dev->mmio_len);
	if (!hdmi_dev->regs) {
		dev_err(dev->dev, "failed to map hdmi mmio\n");
		goto free;
	}

	hdmi_dev->dev = pdev;
	pci_set_drvdata(pdev, hdmi_dev);

	/* Initialize i2c controller */
	ret = oaktrail_hdmi_i2c_init(hdmi_dev->dev);
	if (ret)
		dev_err(dev->dev, "HDMI I2C initialization failed\n");

	dev_priv->hdmi_priv = hdmi_dev;
	oaktrail_hdmi_audio_disable(dev);

	dev_info(dev->dev, "HDMI hardware present.\n");

	return;

free:
	kfree(hdmi_dev);
out:
	return;
}