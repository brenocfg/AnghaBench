#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_9__ {int retries; int /*<<< orphan*/ * lock_ops; int /*<<< orphan*/ * algo; TYPE_2__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct intel_gmbus {unsigned int reg0; int force_bit; TYPE_3__ adapter; struct drm_i915_private* dev_priv; } ;
struct TYPE_7__ {struct pci_dev* pdev; } ;
struct drm_i915_private {struct intel_gmbus* gmbus; int /*<<< orphan*/  gmbus_wait_queue; int /*<<< orphan*/  gmbus_mutex; scalar_t__ gpio_mmio_base; TYPE_1__ drm; } ;
struct TYPE_11__ {scalar_t__ num_pipes; } ;
struct TYPE_10__ {char* name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct intel_gmbus*) ; 
 unsigned int GMBUS_RATE_100KHZ ; 
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  HAS_GMCH_DISPLAY (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 TYPE_6__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PCH_GPIOA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ VLV_DISPLAY_BASE ; 
 TYPE_5__* get_gmbus_pin (struct drm_i915_private*,unsigned int) ; 
 int /*<<< orphan*/  gmbus_algorithm ; 
 int /*<<< orphan*/  gmbus_lock_ops ; 
 int i2c_add_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  i2c_del_adapter (TYPE_3__*) ; 
 scalar_t__ i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gmbus_is_valid_pin (struct drm_i915_private*,unsigned int) ; 
 int /*<<< orphan*/  intel_gpio_setup (struct intel_gmbus*,unsigned int) ; 
 int /*<<< orphan*/  intel_i2c_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

int intel_setup_gmbus(struct drm_i915_private *dev_priv)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;
	struct intel_gmbus *bus;
	unsigned int pin;
	int ret;

	if (INTEL_INFO(dev_priv)->num_pipes == 0)
		return 0;

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		dev_priv->gpio_mmio_base = VLV_DISPLAY_BASE;
	else if (!HAS_GMCH_DISPLAY(dev_priv))
		dev_priv->gpio_mmio_base =
			i915_mmio_reg_offset(PCH_GPIOA) -
			i915_mmio_reg_offset(GPIOA);

	mutex_init(&dev_priv->gmbus_mutex);
	init_waitqueue_head(&dev_priv->gmbus_wait_queue);

	for (pin = 0; pin < ARRAY_SIZE(dev_priv->gmbus); pin++) {
		if (!intel_gmbus_is_valid_pin(dev_priv, pin))
			continue;

		bus = &dev_priv->gmbus[pin];

		bus->adapter.owner = THIS_MODULE;
		bus->adapter.class = I2C_CLASS_DDC;
		snprintf(bus->adapter.name,
			 sizeof(bus->adapter.name),
			 "i915 gmbus %s",
			 get_gmbus_pin(dev_priv, pin)->name);

		bus->adapter.dev.parent = &pdev->dev;
		bus->dev_priv = dev_priv;

		bus->adapter.algo = &gmbus_algorithm;
		bus->adapter.lock_ops = &gmbus_lock_ops;

		/*
		 * We wish to retry with bit banging
		 * after a timed out GMBUS attempt.
		 */
		bus->adapter.retries = 1;

		/* By default use a conservative clock rate */
		bus->reg0 = pin | GMBUS_RATE_100KHZ;

		/* gmbus seems to be broken on i830 */
		if (IS_I830(dev_priv))
			bus->force_bit = 1;

		intel_gpio_setup(bus, pin);

		ret = i2c_add_adapter(&bus->adapter);
		if (ret)
			goto err;
	}

	intel_i2c_reset(dev_priv);

	return 0;

err:
	while (pin--) {
		if (!intel_gmbus_is_valid_pin(dev_priv, pin))
			continue;

		bus = &dev_priv->gmbus[pin];
		i2c_del_adapter(&bus->adapter);
	}
	return ret;
}