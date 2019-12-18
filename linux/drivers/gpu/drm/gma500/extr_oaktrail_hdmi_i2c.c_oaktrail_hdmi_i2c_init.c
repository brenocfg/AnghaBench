#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct oaktrail_hdmi_dev {struct hdmi_i2c_dev* i2c_dev; } ;
struct hdmi_i2c_dev {int /*<<< orphan*/  i2c_lock; int /*<<< orphan*/  complete; int /*<<< orphan*/  status; TYPE_1__* adap; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_STAT_INIT ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int i2c_add_numbered_adapter (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_1__*,struct oaktrail_hdmi_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hdmi_i2c_dev*) ; 
 struct hdmi_i2c_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ oaktrail_hdmi_i2c_adapter ; 
 int /*<<< orphan*/  oaktrail_hdmi_i2c_gpio_fix () ; 
 int /*<<< orphan*/  oaktrail_hdmi_i2c_handler ; 
 struct oaktrail_hdmi_dev* pci_get_drvdata (struct pci_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct oaktrail_hdmi_dev*) ; 

int oaktrail_hdmi_i2c_init(struct pci_dev *dev)
{
	struct oaktrail_hdmi_dev *hdmi_dev;
	struct hdmi_i2c_dev *i2c_dev;
	int ret;

	hdmi_dev = pci_get_drvdata(dev);

	i2c_dev = kzalloc(sizeof(struct hdmi_i2c_dev), GFP_KERNEL);
	if (i2c_dev == NULL) {
		DRM_ERROR("Can't allocate interface\n");
		ret = -ENOMEM;
		goto exit;
	}

	i2c_dev->adap = &oaktrail_hdmi_i2c_adapter;
	i2c_dev->status = I2C_STAT_INIT;
	init_completion(&i2c_dev->complete);
	mutex_init(&i2c_dev->i2c_lock);
	i2c_set_adapdata(&oaktrail_hdmi_i2c_adapter, hdmi_dev);
	hdmi_dev->i2c_dev = i2c_dev;

	/* Enable HDMI I2C function on gpio */
	oaktrail_hdmi_i2c_gpio_fix();

	/* request irq */
	ret = request_irq(dev->irq, oaktrail_hdmi_i2c_handler, IRQF_SHARED,
			  oaktrail_hdmi_i2c_adapter.name, hdmi_dev);
	if (ret) {
		DRM_ERROR("Failed to request IRQ for I2C controller\n");
		goto err;
	}

	/* Adapter registration */
	ret = i2c_add_numbered_adapter(&oaktrail_hdmi_i2c_adapter);
	return ret;

err:
	kfree(i2c_dev);
exit:
	return ret;
}